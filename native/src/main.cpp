#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <winreg.h>
#include <dwmapi.h>
#include <cstdio>
#include <cstdint>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "advapi32.lib")

namespace {

constexpr wchar_t kWindowClass[] = L"TharuOptimizerWindow";
constexpr wchar_t kWindowTitle[] = L"THARU OPTIMIZER — Windows + Minecraft";
constexpr UINT_PTR kMetricsTimer = 1;
constexpr UINT_PTR kPreviewTimer = 2;

struct Palette {
    COLORREF background = RGB(9, 12, 17);
    COLORREF sidebar = RGB(12, 17, 24);
    COLORREF surface = RGB(16, 22, 31);
    COLORREF surfaceRaised = RGB(20, 28, 39);
    COLORREF surfaceHover = RGB(27, 37, 49);
    COLORREF border = RGB(34, 44, 57);
    COLORREF text = RGB(241, 245, 249);
    COLORREF muted = RGB(137, 151, 168);
    COLORREF dim = RGB(104, 118, 136);
    COLORREF lime = RGB(186, 243, 107);
    COLORREF blue = RGB(134, 168, 255);
    COLORREF purple = RGB(193, 156, 255);
    COLORREF orange = RGB(255, 191, 115);
    COLORREF red = RGB(255, 133, 138);
    COLORREF track = RGB(39, 49, 63);
};

const Palette kColors{};

int gDpi = 96;
int gPage = 0;
int gHoveredTarget = -1;
int gHardwareTab = 0;
int gProfile = 0;
int gMinecraftProfile = 0;
int gMinecraftRam = 6;
int gJvmPreset = 0;
int gDnsProfile = 0;
bool gTrackingMouse = false;
bool gSettingsPrefs[3] = {true, false, false};
HWND gMainWindow = nullptr;

struct Metrics {
    double cpuPercent = 0.0;
    bool cpuReady = false;
    ULONGLONG previousIdle = 0;
    ULONGLONG previousKernel = 0;
    ULONGLONG previousUser = 0;
    DWORD memoryPercent = 0;
    ULONGLONG memoryTotal = 0;
    ULONGLONG memoryAvailable = 0;
    ULONGLONG diskTotal = 0;
    ULONGLONG diskAvailable = 0;
    std::wstring processorName;
    std::wstring graphicsName;
};

Metrics gMetrics;
std::wstring gStatus = L"Read-only system metrics · all optimizer actions are preview-only";
std::wstring gTaskLabel;
int gTaskProgress = 0;
enum class TaskMode { None, Scan, NetworkTest, Repair };
TaskMode gTaskMode = TaskMode::None;

struct CleanerItem {
    const wchar_t* name;
    const wchar_t* size;
    int sampleMb;
    bool lowRisk;
    bool selected;
};

std::vector<CleanerItem> gCleanerItems = {
    {L"Temporary files", L"2.4 GB", 2458, true, true},
    {L"DirectX Shader Cache", L"846 MB", 846, true, true},
    {L"Delivery Optimization cache", L"611 MB", 611, true, true},
    {L"Thumbnail cache", L"210 MB", 210, true, true},
    {L"Windows Update cache", L"1.3 GB", 1331, false, false},
    {L"Prefetch data", L"128 MB", 128, false, false},
    {L"Recycle Bin", L"7.9 GB", 8050, false, false},
    {L"Browser cache", L"1.1 GB", 1106, true, true},
    {L"DNS cache", L"0 B on disk", 0, false, false},
    {L"Crash dumps", L"334 MB", 334, false, false},
    {L"Error reports", L"76 MB", 76, true, true},
    {L"Old Windows logs", L"18 MB", 18, true, true},
    {L"App cache", L"12 MB", 12, false, false},
    {L"Defender history cache", L"8 MB", 8, false, false},
};

struct StartupItem {
    const wchar_t* name;
    const wchar_t* impact;
    const wchar_t* publisher;
    bool enabled;
};

std::vector<StartupItem> gStartupItems = {
    {L"Discord", L"Medium", L"Discord Inc.", true},
    {L"Steam", L"High", L"Valve Corporation", true},
    {L"OneDrive", L"Medium", L"Microsoft", true},
    {L"Epic Games Launcher", L"High", L"Epic Games", true},
    {L"Microsoft Teams", L"High", L"Microsoft", true},
    {L"Spotify", L"Low", L"Spotify AB", false},
    {L"Minecraft Launcher", L"Low", L"Microsoft Studios", false},
    {L"Adobe Updater", L"Medium", L"Adobe Inc.", true},
};

struct PreviewToggle {
    const wchar_t* label;
    const wchar_t* detail;
    bool enabled;
};

std::vector<PreviewToggle> gGamingToggles = {
    {L"Windows Game Mode", L"Example state · confirm in Windows Settings", true},
    {L"GPU scheduling (HAGS)", L"Support varies by Windows build and driver", false},
    {L"Fullscreen optimizations", L"Compare per game; behavior can vary", true},
    {L"Xbox Game Bar", L"Keep if you use its overlay or shortcuts", true},
    {L"Background capture", L"May use CPU, GPU, storage, and memory", false},
};

std::vector<PreviewToggle> gPrivacyToggles = {
    {L"Advertising ID", L"Optional Windows privacy control · sample state", true},
    {L"Optional diagnostic data", L"Review feature and support impact first", true},
    {L"Activity history", L"Review local and sync controls", true},
    {L"Background app permissions", L"Controls vary by app and Windows version", true},
};

struct ServiceItem {
    const wchar_t* name;
    const wchar_t* state;
    const wchar_t* startup;
    const wchar_t* recommendation;
};

const std::vector<ServiceItem> gServices = {
    {L"SysMain", L"Running", L"Automatic", L"Keep default"},
    {L"Windows Search", L"Running", L"Automatic", L"Keep default"},
    {L"Print Spooler", L"Running", L"Automatic", L"Conditional"},
    {L"Xbox Live Auth Manager", L"Stopped", L"Manual", L"Keep default"},
    {L"Gaming Services", L"Running", L"Automatic", L"Keep default"},
    {L"Diagnostic Policy Service", L"Running", L"Automatic", L"Keep default"},
    {L"Third-party updater", L"Running", L"Automatic", L"Review vendor"},
};

struct NavItem { const wchar_t* label; int page; };
struct NavGroup { const wchar_t* label; std::vector<NavItem> items; };

// Page ids are stable so targets can be routed without platform-specific frameworks.
enum Page : int {
    Overview = 0, Cleaner, Gaming, Minecraft, Network, Hardware, Startup, Services,
    Privacy, Debloat, Repair, Restore, Settings, PageCount
};

enum class Action {
    Navigate,
    QuickScan,
    Optimize,
    CreateRestore,
    CleanerToggle,
    CleanerSelectSafe,
    CleanerReview,
    GamingProfile,
    GamingToggle,
    MinecraftProfile,
    RamDown,
    RamUp,
    JvmPreset,
    MinecraftRescan,
    ProcessReview,
    BackgroundReview,
    NetworkTest,
    DnsChoice,
    NetworkAdvanced,
    HardwareTab,
    StartupToggle,
    ServiceReview,
    DebloatReview,
    RepairRun,
    Undo,
    ExportPreview,
    SettingsToggle,
    About,
};

struct HitTarget {
    RECT rect{};
    Action action{};
    int value = 0;
    int page = Overview;
    bool disabled = false;
};

std::vector<HitTarget> gTargets;
std::map<std::pair<int, int>, HFONT> gFonts;

std::vector<NavGroup> makeNavGroups() {
    return {
        {L"WORKSPACE", {{L"Overview", Overview}, {L"Windows Cleaner", Cleaner}, {L"Gaming", Gaming}, {L"Minecraft", Minecraft}}},
        {L"PERFORMANCE", {{L"Network", Network}, {L"Hardware & BIOS", Hardware}}},
        {L"WINDOWS", {{L"Startup Manager", Startup}, {L"Services", Services}, {L"Privacy", Privacy}, {L"Debloat", Debloat}, {L"System Repair", Repair}}},
        {L"SAFETY", {{L"Restore Center", Restore}, {L"Settings", Settings}}},
    };
}

const std::vector<NavGroup> gNavGroups = makeNavGroups();

int px(int value) { return MulDiv(value, gDpi, 96); }

RECT makeRect(int left, int top, int right, int bottom) {
    return RECT{px(left), px(top), px(right), px(bottom)};
}

HFONT fontFor(int points, int weight) {
    const auto key = std::make_pair(points, weight);
    const auto found = gFonts.find(key);
    if (found != gFonts.end()) return found->second;
    HFONT font = CreateFontW(-MulDiv(points, gDpi, 72), 0, 0, 0, weight, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
    gFonts.emplace(key, font);
    return font;
}

void destroyFonts() {
    for (auto& item : gFonts) if (item.second) DeleteObject(item.second);
    gFonts.clear();
}

void drawText(HDC dc, const std::wstring& value, RECT rect, COLORREF color,
              int points = 10, int weight = FW_NORMAL, UINT flags = DT_LEFT | DT_VCENTER | DT_SINGLELINE) {
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, color);
    HFONT font = fontFor(points, weight);
    HGDIOBJ previous = SelectObject(dc, font);
    DrawTextW(dc, value.c_str(), static_cast<int>(value.size()), &rect, flags | DT_NOPREFIX);
    SelectObject(dc, previous);
}

void drawRoundRect(HDC dc, RECT rect, COLORREF fill, COLORREF stroke, int radius = 11) {
    HBRUSH brush = CreateSolidBrush(fill);
    HPEN pen = CreatePen(PS_SOLID, px(1), stroke);
    HGDIOBJ oldBrush = SelectObject(dc, brush);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    RoundRect(dc, rect.left, rect.top, rect.right, rect.bottom, px(radius), px(radius));
    SelectObject(dc, oldBrush);
    SelectObject(dc, oldPen);
    DeleteObject(brush);
    DeleteObject(pen);
}

void fillRect(HDC dc, RECT rect, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(dc, &rect, brush);
    DeleteObject(brush);
}

void line(HDC dc, int x1, int y1, int x2, int y2, COLORREF color) {
    HPEN pen = CreatePen(PS_SOLID, px(1), color);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    MoveToEx(dc, x1, y1, nullptr);
    LineTo(dc, x2, y2);
    SelectObject(dc, oldPen);
    DeleteObject(pen);
}

void addTarget(RECT rect, Action action, int value = 0, int page = Overview, bool disabled = false) {
    gTargets.push_back(HitTarget{rect, action, value, page, disabled});
}

bool hitRect(const RECT& rect, POINT point) {
    return PtInRect(&rect, point) != FALSE;
}

int targetAt(POINT point) {
    for (int i = static_cast<int>(gTargets.size()) - 1; i >= 0; --i) {
        if (!gTargets[static_cast<size_t>(i)].disabled && hitRect(gTargets[static_cast<size_t>(i)].rect, point)) return i;
    }
    return -1;
}

void drawPill(HDC dc, RECT rect, const std::wstring& label, COLORREF tint) {
    drawRoundRect(dc, rect, RGB(23, 31, 41), RGB(48, 61, 78), 9);
    RECT textRect = rect;
    InflateRect(&textRect, -px(7), 0);
    drawText(dc, label, textRect, tint, 8, FW_SEMIBOLD);
}

void drawButton(HDC dc, RECT rect, const std::wstring& label, Action action, int value = 0,
                bool primary = false, bool disabled = false, int page = Overview) {
    const int targetIndex = static_cast<int>(gTargets.size());
    addTarget(rect, action, value, page, disabled);
    const bool hovered = targetIndex == gHoveredTarget && !disabled;
    COLORREF fill = primary ? kColors.lime : (hovered ? kColors.surfaceHover : kColors.surfaceRaised);
    COLORREF stroke = primary ? RGB(203, 255, 148) : kColors.border;
    COLORREF text = primary ? RGB(17, 23, 12) : kColors.text;
    if (disabled) { fill = kColors.surface; text = kColors.dim; }
    drawRoundRect(dc, rect, fill, stroke, 8);
    drawText(dc, label, rect, text, 9, FW_SEMIBOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void drawCard(HDC dc, RECT rect, const std::wstring& title, const std::wstring& subtitle = L"") {
    drawRoundRect(dc, rect, kColors.surface, kColors.border, 12);
    RECT titleRect{rect.left + px(15), rect.top + px(11), rect.right - px(15), rect.top + px(33)};
    drawText(dc, title, titleRect, kColors.text, 11, FW_SEMIBOLD);
    if (!subtitle.empty()) {
        RECT subRect{rect.left + px(15), rect.top + px(33), rect.right - px(15), rect.top + px(52)};
        drawText(dc, subtitle, subRect, kColors.muted, 8, FW_NORMAL);
    }
}

void drawBar(HDC dc, RECT rect, double percent, COLORREF color) {
    drawRoundRect(dc, rect, kColors.track, kColors.track, 5);
    const int width = rect.right - rect.left;
    const int fill = static_cast<int>(width * (percent < 0 ? 0 : percent > 100 ? 100 : percent) / 100.0);
    if (fill > 0) {
        RECT filled{rect.left, rect.top, rect.left + fill, rect.bottom};
        drawRoundRect(dc, filled, color, color, 5);
    }
}

std::wstring formatBytes(ULONGLONG bytes) {
    const double gb = static_cast<double>(bytes) / (1024.0 * 1024.0 * 1024.0);
    std::wostringstream out;
    if (gb >= 1024.0) out << std::fixed << std::setprecision(1) << gb / 1024.0 << L" TB";
    else out << std::fixed << std::setprecision(1) << gb << L" GB";
    return out.str();
}

std::wstring formatSampleMb(int mb) {
    if (mb <= 0) return L"0 B";
    if (mb >= 1024) {
        std::wostringstream out;
        out << std::fixed << std::setprecision(1) << static_cast<double>(mb) / 1024.0 << L" GB";
        return out.str();
    }
    return std::to_wstring(mb) + L" MB";
}

ULONGLONG fileTimeValue(const FILETIME& value) {
    ULARGE_INTEGER number{};
    number.LowPart = value.dwLowDateTime;
    number.HighPart = value.dwHighDateTime;
    return number.QuadPart;
}

std::wstring readProcessorName() {
    HKEY key = nullptr;
    const wchar_t* path = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, path, 0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS) return L"Processor name unavailable";
    wchar_t value[256]{};
    DWORD bytes = sizeof(value);
    DWORD type = 0;
    const LONG result = RegQueryValueExW(key, L"ProcessorNameString", nullptr, &type,
        reinterpret_cast<LPBYTE>(value), &bytes);
    RegCloseKey(key);
    if (result != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ)) return L"Processor name unavailable";
    value[255] = L'\0';
    return value;
}

std::wstring readGraphicsName() {
    DISPLAY_DEVICEW display{};
    display.cb = sizeof(display);
    if (EnumDisplayDevicesW(nullptr, 0, &display, 0) && display.DeviceString[0] != L'\0') return display.DeviceString;
    return L"Graphics adapter unavailable";
}

void refreshMetrics() {
    FILETIME idle{}, kernel{}, user{};
    if (GetSystemTimes(&idle, &kernel, &user)) {
        const ULONGLONG idleNow = fileTimeValue(idle);
        const ULONGLONG kernelNow = fileTimeValue(kernel);
        const ULONGLONG userNow = fileTimeValue(user);
        if (gMetrics.previousKernel != 0 || gMetrics.previousUser != 0) {
            const ULONGLONG idleDelta = idleNow - gMetrics.previousIdle;
            const ULONGLONG totalDelta = (kernelNow - gMetrics.previousKernel) + (userNow - gMetrics.previousUser);
            if (totalDelta > 0 && idleDelta <= totalDelta) {
                gMetrics.cpuPercent = 100.0 * static_cast<double>(totalDelta - idleDelta) / static_cast<double>(totalDelta);
                gMetrics.cpuReady = true;
            }
        }
        gMetrics.previousIdle = idleNow;
        gMetrics.previousKernel = kernelNow;
        gMetrics.previousUser = userNow;
    }

    MEMORYSTATUSEX memory{};
    memory.dwLength = sizeof(memory);
    if (GlobalMemoryStatusEx(&memory)) {
        gMetrics.memoryPercent = memory.dwMemoryLoad;
        gMetrics.memoryTotal = memory.ullTotalPhys;
        gMetrics.memoryAvailable = memory.ullAvailPhys;
    }

    ULARGE_INTEGER available{}, total{}, totalFree{};
    if (GetDiskFreeSpaceExW(L"C:\\", &available, &total, &totalFree)) {
        gMetrics.diskTotal = total.QuadPart;
        gMetrics.diskAvailable = available.QuadPart;
    }

    if (gMetrics.processorName.empty()) gMetrics.processorName = readProcessorName();
    if (gMetrics.graphicsName.empty()) gMetrics.graphicsName = readGraphicsName();
}

std::wstring currentPageName(int page) {
    for (const auto& group : gNavGroups)
        for (const auto& item : group.items)
            if (item.page == page) return item.label;
    return L"Overview";
}

void drawSidebar(HDC dc, int clientHeight) {
    const int sidebarWidth = px(242);
    RECT side{0, 0, sidebarWidth, clientHeight};
    fillRect(dc, side, kColors.sidebar);
    line(dc, 0, 0, 0, clientHeight, kColors.border);
    line(dc, sidebarWidth - px(1), 0, sidebarWidth - px(1), clientHeight, kColors.border);

    RECT logoRect = makeRect(18, 18, 54, 54);
    drawRoundRect(dc, logoRect, RGB(27, 38, 28), RGB(60, 82, 47), 10);
    drawText(dc, L"T", logoRect, kColors.lime, 17, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, L"THARU", makeRect(63, 19, 142, 37), kColors.text, 12, FW_BOLD);
    drawText(dc, L"OPTIMIZER", makeRect(63, 37, 142, 51), kColors.muted, 7, FW_SEMIBOLD);
    RECT previewRect = makeRect(172, 25, 224, 43);
    drawPill(dc, previewRect, L"PREVIEW", kColors.lime);

    RECT device = makeRect(12, 69, 230, 119);
    drawRoundRect(dc, device, RGB(16, 23, 32), kColors.border, 9);
    RECT monitor = makeRect(22, 79, 52, 108);
    drawRoundRect(dc, monitor, RGB(24, 35, 50), RGB(43, 61, 83), 7);
    drawText(dc, L"PC", monitor, kColors.blue, 8, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, L"This device", makeRect(61, 77, 179, 95), kColors.text, 9, FW_SEMIBOLD);
    drawText(dc, L"Local read-only metrics", makeRect(61, 95, 199, 110), kColors.muted, 7, FW_NORMAL);

    int y = 130;
    for (const auto& group : gNavGroups) {
        RECT groupLabel = makeRect(20, y, 220, y + 14);
        drawText(dc, group.label, groupLabel, kColors.dim, 7, FW_SEMIBOLD);
        y += 16;
        for (const auto& item : group.items) {
            RECT button = makeRect(11, y, 231, y + 31);
            const bool active = item.page == static_cast<int>(gPage);
            const bool hovered = static_cast<int>(gTargets.size()) == gHoveredTarget;
            const COLORREF fill = active ? RGB(28, 42, 34) : (hovered ? RGB(22, 31, 41) : kColors.sidebar);
            const COLORREF stroke = active ? RGB(56, 81, 46) : kColors.sidebar;
            drawRoundRect(dc, button, fill, stroke, 8);
            if (active) {
                RECT accent{button.left + px(1), button.top + px(7), button.left + px(3), button.bottom - px(7)};
                fillRect(dc, accent, kColors.lime);
            }
            RECT iconRect{button.left + px(12), button.top + px(5), button.left + px(31), button.bottom - px(5)};
            drawRoundRect(dc, iconRect, active ? RGB(37, 54, 39) : RGB(22, 29, 39), active ? RGB(56, 81, 46) : RGB(35, 45, 58), 6);
            std::wstring initials = item.page == Minecraft ? L"MC" : item.page == Cleaner ? L"CL" : item.page == Gaming ? L"G" :
                item.page == Overview ? L"O" : item.page == Network ? L"N" : item.page == Hardware ? L"H" :
                item.page == Startup ? L"S" : item.page == Services ? L"SV" : item.page == Privacy ? L"P" :
                item.page == Debloat ? L"D" : item.page == Repair ? L"R" : item.page == Restore ? L"↶" : L"⚙";
            drawText(dc, initials, iconRect, active ? kColors.lime : kColors.muted, 7, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            RECT labelRect{button.left + px(41), button.top, button.right - px(8), button.bottom};
            drawText(dc, item.label, labelRect, active ? RGB(228, 242, 214) : RGB(164, 176, 190), 8, active ? FW_SEMIBOLD : FW_NORMAL);
            addTarget(button, Action::Navigate, 0, item.page);
            y += 33;
        }
        y += 5;
    }

    const int footerTop = clientHeight - px(64);
    line(dc, px(12), footerTop, sidebarWidth - px(12), footerTop, RGB(31, 41, 53));
    RECT safeIcon = makeRect(17, 0, 43, 26);
    OffsetRect(&safeIcon, 0, footerTop + px(12));
    drawRoundRect(dc, safeIcon, RGB(26, 39, 29), RGB(43, 66, 39), 7);
    drawText(dc, L"OK", safeIcon, kColors.lime, 7, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, L"Safety first", makeRect(51, footerTop + 8, 207, footerTop + 25), kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, L"No optimizer actions are applied", makeRect(51, footerTop + 25, 226, footerTop + 41), kColors.muted, 6, FW_NORMAL);
}

void drawTopbar(HDC dc, int clientWidth) {
    const int sidebarWidth = px(242);
    RECT top{sidebarWidth, 0, clientWidth, px(61)};
    fillRect(dc, top, RGB(10, 14, 20));
    line(dc, sidebarWidth, px(60), clientWidth, px(60), RGB(28, 38, 50));
    drawText(dc, L"THARU", makeRect(270, 17, 316, 43), kColors.dim, 7, FW_SEMIBOLD);
    drawText(dc, L"/", makeRect(317, 17, 327, 43), RGB(67, 79, 94), 8, FW_NORMAL, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, currentPageName(gPage), makeRect(332, 17, 530, 43), RGB(204, 214, 224), 8, FW_SEMIBOLD);
    RECT status = makeRect(0, 18, 422, 43);
    OffsetRect(&status, clientWidth - px(479), 0);
    drawRoundRect(dc, status, RGB(25, 29, 31), RGB(67, 57, 42), 12);
    RECT dot{status.left + px(10), status.top + px(9), status.left + px(16), status.top + px(15)};
    HBRUSH dotBrush = CreateSolidBrush(kColors.orange);
    FillRect(dc, &dot, dotBrush);
    DeleteObject(dotBrush);
    drawText(dc, L"INTERACTIVE PREVIEW", RECT{status.left + px(23), status.top, status.right - px(48), status.bottom}, RGB(218, 205, 186), 7, FW_SEMIBOLD);
    drawText(dc, L"DEMO", RECT{status.right - px(43), status.top, status.right - px(7), status.bottom}, kColors.orange, 7, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void drawHeading(HDC dc, int x, int y, int width, const std::wstring& title, const std::wstring& subtitle, const std::wstring& tag = L"") {
    drawText(dc, title, makeRect(x, y, x + width, y + 35), kColors.text, 21, FW_BOLD);
    drawText(dc, subtitle, makeRect(x, y + 38, x + width, y + 60), kColors.muted, 8, FW_NORMAL);
    if (!tag.empty()) {
        RECT badge = makeRect(x + width - 145, y + 5, x + width, y + 27);
        drawPill(dc, badge, tag, kColors.blue);
    }
}

void drawMetricCard(HDC dc, RECT rect, const std::wstring& label, const std::wstring& value,
                    const std::wstring& detail, double percent, COLORREF tint) {
    drawRoundRect(dc, rect, kColors.surface, kColors.border, 10);
    RECT labelRect{rect.left + px(12), rect.top + px(10), rect.right - px(12), rect.top + px(28)};
    drawText(dc, label, labelRect, kColors.muted, 8, FW_SEMIBOLD);
    RECT valueRect{rect.left + px(12), rect.top + px(34), rect.right - px(12), rect.top + px(61)};
    drawText(dc, value, valueRect, kColors.text, 16, FW_BOLD);
    RECT detailRect{rect.left + px(12), rect.top + px(62), rect.right - px(12), rect.top + px(79)};
    drawText(dc, detail, detailRect, kColors.muted, 7, FW_NORMAL);
    RECT bar{rect.left + px(12), rect.bottom - px(14), rect.right - px(12), rect.bottom - px(9)};
    drawBar(dc, bar, percent, tint);
}

void drawProgress(HDC dc, RECT rect, double percent, COLORREF tint = kColors.lime) {
    drawRoundRect(dc, rect, kColors.track, kColors.track, 4);
    RECT bar = rect;
    bar.right = bar.left + static_cast<int>((rect.right - rect.left) * percent / 100.0);
    if (bar.right > bar.left) drawRoundRect(dc, bar, tint, tint, 4);
}

std::wstring healthSummary() {
    if (gTaskMode == TaskMode::Scan && gTaskProgress >= 100) return L"Preview scan complete · no files accessed";
    if (gMetrics.cpuReady) return L"Live local CPU, memory, and disk readings";
    return L"Checking local hardware metrics…";
}

void drawOverview(HDC dc, RECT area, HWND hwnd) {
    const int contentX = px(270);
    const int right = area.right - px(28);
    const int width = right - contentX;
    drawHeading(dc, 270, 78, MulDiv(width, 96, gDpi), L"Your PC, in balance.", L"Safe-first tools for Windows and Minecraft · local sample profile", L"SAMPLE DEVICE");

    const int gap = px(12);
    const int rowTop = px(151);
    const int rowHeight = px(190);
    const int leftWidth = (width - gap) * 58 / 100;
    RECT health{contentX, rowTop, contentX + leftWidth, rowTop + rowHeight};
    RECT performance{health.right + gap, rowTop, right, rowTop + rowHeight};
    drawRoundRect(dc, health, RGB(19, 27, 34), RGB(43, 58, 48), 13);
    drawText(dc, L"SYSTEM HEALTH · SAMPLE SCORE", RECT{health.left + px(17), health.top + px(13), health.right - px(15), health.top + px(31)}, kColors.muted, 7, FW_SEMIBOLD);
    RECT statusPill = makeRect(0, 0, 83, 20);
    OffsetRect(&statusPill, health.right - px(100), health.top + px(12));
    drawPill(dc, statusPill, L"GOOD SHAPE", kColors.lime);

    RECT outerRing{health.left + px(19), health.top + px(47), health.left + px(121), health.top + px(149)};
    HBRUSH ringBrush = CreateSolidBrush(RGB(20, 29, 27));
    HPEN ringPen = CreatePen(PS_SOLID, px(4), kColors.lime);
    HGDIOBJ oldBrush = SelectObject(dc, ringBrush);
    HGDIOBJ oldPen = SelectObject(dc, ringPen);
    Ellipse(dc, outerRing.left, outerRing.top, outerRing.right, outerRing.bottom);
    SelectObject(dc, oldBrush);
    SelectObject(dc, oldPen);
    DeleteObject(ringBrush);
    DeleteObject(ringPen);
    RECT ringText = outerRing;
    drawText(dc, L"86", RECT{ringText.left, ringText.top + px(15), ringText.right, ringText.bottom - px(14)}, kColors.text, 20, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, L"SAMPLE", RECT{ringText.left, ringText.top + px(61), ringText.right, ringText.bottom - px(18)}, kColors.muted, 6, FW_SEMIBOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    drawText(dc, L"Nothing changes without you.", RECT{health.left + px(137), health.top + px(53), health.right - px(16), health.top + px(79)}, kColors.text, 12, FW_SEMIBOLD);
    drawText(dc, L"Run a sample review, check available space, and choose a profile. This build does not modify Windows.", RECT{health.left + px(137), health.top + px(82), health.right - px(18), health.top + px(121)}, kColors.muted, 8, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_TOP);
    RECT scanButton = makeRect(0, 0, 130, 30);
    OffsetRect(&scanButton, health.left + px(137), health.top + px(129));
    drawButton(dc, scanButton, gTaskMode == TaskMode::Scan && gTaskProgress < 100 ? L"Scanning…" : L"Run quick scan", Action::QuickScan,
        0, false, gTaskMode != TaskMode::None && gTaskProgress < 100);
    drawText(dc, healthSummary(), RECT{health.left + px(17), health.bottom - px(25), health.right - px(14), health.bottom - px(9)}, kColors.muted, 7, FW_NORMAL);

    drawRoundRect(dc, performance, kColors.surface, kColors.border, 13);
    drawText(dc, L"PERFORMANCE SNAPSHOT", RECT{performance.left + px(16), performance.top + px(14), performance.right - px(14), performance.top + px(31)}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"Live local readings", RECT{performance.left + px(16), performance.top + px(34), performance.right - px(12), performance.top + px(51)}, kColors.text, 10, FW_SEMIBOLD);

    const std::wstring cpuValue = gMetrics.cpuReady ? std::to_wstring(static_cast<int>(gMetrics.cpuPercent + 0.5)) + L"%" : L"—";
    const std::wstring memValue = std::to_wstring(gMetrics.memoryPercent) + L"%";
    const std::wstring diskValue = gMetrics.diskTotal ? std::to_wstring(static_cast<int>(100.0 * (1.0 - static_cast<double>(gMetrics.diskAvailable) / gMetrics.diskTotal))) + L"%" : L"—";
    struct PerfRow { const wchar_t* name; std::wstring value; double percent; COLORREF tint; };
    const std::vector<PerfRow> perfRows = {
        {L"CPU", cpuValue, gMetrics.cpuPercent, kColors.lime},
        {L"Memory", memValue, static_cast<double>(gMetrics.memoryPercent), kColors.blue},
        {L"Disk", diskValue, gMetrics.diskTotal ? 100.0 * (1.0 - static_cast<double>(gMetrics.diskAvailable) / gMetrics.diskTotal) : 0.0, kColors.purple},
    };
    int perfY = performance.top + px(67);
    for (const auto& row : perfRows) {
        drawText(dc, row.name, RECT{performance.left + px(16), perfY, performance.left + px(69), perfY + px(16)}, kColors.muted, 7, FW_NORMAL);
        RECT bar{performance.left + px(72), perfY + px(5), performance.right - px(58), perfY + px(11)};
        drawProgress(dc, bar, row.percent, row.tint);
        drawText(dc, row.value, RECT{performance.right - px(51), perfY, performance.right - px(13), perfY + px(16)}, kColors.text, 7, FW_SEMIBOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
        perfY += px(28);
    }
    line(dc, performance.left + px(14), performance.bottom - px(31), performance.right - px(14), performance.bottom - px(31), kColors.border);
    drawText(dc, L"Network test", RECT{performance.left + px(15), performance.bottom - px(27), performance.right - px(96), performance.bottom - px(10)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"Not run", RECT{performance.right - px(91), performance.bottom - px(27), performance.right - px(14), performance.bottom - px(10)}, kColors.orange, 7, FW_SEMIBOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

    const int metricTop = rowTop + rowHeight + px(12);
    const int metricHeight = px(97);
    const int metricGap = px(9);
    const int metricWidth = (width - metricGap * 3) / 4;
    const std::wstring cpuName = gMetrics.processorName.empty() ? L"Processor" : gMetrics.processorName;
    const std::wstring memUsed = gMetrics.memoryTotal ? formatBytes(gMetrics.memoryTotal - gMetrics.memoryAvailable) + L" used" : L"Not available";
    const std::wstring gpuName = gMetrics.graphicsName.empty() ? L"Display adapter" : gMetrics.graphicsName;
    const std::wstring diskFree = gMetrics.diskAvailable ? formatBytes(gMetrics.diskAvailable) + L" free" : L"Drive unavailable";
    std::vector<std::tuple<std::wstring, std::wstring, std::wstring, double, COLORREF>> metricData = {
        {L"CPU", cpuValue, cpuName, gMetrics.cpuPercent, kColors.lime},
        {L"RAM", formatBytes(gMetrics.memoryTotal - gMetrics.memoryAvailable), memUsed, static_cast<double>(gMetrics.memoryPercent), kColors.purple},
        {L"GPU", L"—", gpuName, 0, kColors.orange},
        {L"C: drive", diskValue, diskFree, gMetrics.diskTotal ? 100.0 * (1.0 - static_cast<double>(gMetrics.diskAvailable) / gMetrics.diskTotal) : 0.0, kColors.blue},
    };
    for (size_t i = 0; i < metricData.size(); ++i) {
        const int left = contentX + static_cast<int>(i) * (metricWidth + metricGap);
        RECT card{left, metricTop, left + metricWidth, metricTop + metricHeight};
        drawMetricCard(dc, card, std::get<0>(metricData[i]), std::get<1>(metricData[i]), std::get<2>(metricData[i]), std::get<3>(metricData[i]), std::get<4>(metricData[i]));
    }

    const int detailsTop = metricTop + metricHeight + px(9);
    const int detailHeight = px(48);
    const int detailGap = px(8);
    const int detailWidth = (width - detailGap * 3) / 4;
    const std::vector<std::pair<std::wstring, std::wstring>> details = {
        {L"Network latency", L"Not tested"},
        {L"Startup entries", L"Sample list · 6 enabled"},
        {L"Temp & cache found", L"Preview estimate only"},
        {L"Last optimization", L"Never"},
    };
    for (size_t i = 0; i < details.size(); ++i) {
        const int left = contentX + static_cast<int>(i) * (detailWidth + detailGap);
        RECT detail{left, detailsTop, left + detailWidth, detailsTop + detailHeight};
        drawRoundRect(dc, detail, RGB(14, 20, 28), kColors.border, 8);
        drawText(dc, details[i].first, RECT{detail.left + px(9), detail.top + px(5), detail.right - px(8), detail.top + px(21)}, kColors.muted, 7, FW_NORMAL);
        drawText(dc, details[i].second, RECT{detail.left + px(9), detail.top + px(23), detail.right - px(8), detail.bottom - px(4)}, kColors.text, 8, FW_SEMIBOLD);
    }

    const int lowerTop = detailsTop + detailHeight + px(11);
    const int lowerHeight = px(124);
    const int lowerLeftWidth = width * 61 / 100;
    RECT optimize{contentX, lowerTop, contentX + lowerLeftWidth, lowerTop + lowerHeight};
    RECT recent{optimize.right + gap, lowerTop, right, lowerTop + lowerHeight};
    drawRoundRect(dc, optimize, RGB(17, 25, 31), kColors.border, 12);
    drawText(dc, L"YOUR NEXT STEPS", RECT{optimize.left + px(14), optimize.top + px(11), optimize.right - px(12), optimize.top + px(25)}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"Ready when you are.", RECT{optimize.left + px(14), optimize.top + px(28), optimize.right - px(12), optimize.top + px(48)}, kColors.text, 11, FW_SEMIBOLD);
    drawText(dc, L"Safe profile · restore-first · sample estimates", RECT{optimize.left + px(14), optimize.top + px(51), optimize.right - px(12), optimize.top + px(67)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"• Review cleaner categories     • Check gaming settings     • Minecraft Java & RAM guide", RECT{optimize.left + px(14), optimize.top + px(75), optimize.right - px(14), optimize.top + px(93)}, RGB(178, 192, 205), 7, FW_NORMAL);
    RECT optimizeButton = makeRect(0, 0, 153, 29);
    OffsetRect(&optimizeButton, optimize.left + px(14), optimize.top + px(91));
    drawButton(dc, optimizeButton, L"OPTIMIZE NOW", Action::Optimize, 0, true);

    drawRoundRect(dc, recent, kColors.surface, kColors.border, 12);
    drawText(dc, L"RECENT ACTIVITY", RECT{recent.left + px(14), recent.top + px(12), recent.right - px(12), recent.top + px(30)}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"Read-only device metrics refreshed", RECT{recent.left + px(14), recent.top + px(40), recent.right - px(12), recent.top + px(59)}, kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, L"This session · local only", RECT{recent.left + px(14), recent.top + px(61), recent.right - px(12), recent.top + px(77)}, kColors.muted, 7, FW_NORMAL);
    RECT openRestore = makeRect(0, 0, 132, 27);
    OffsetRect(&openRestore, recent.left + px(14), recent.top + px(87));
    drawButton(dc, openRestore, L"Open Restore Center", Action::Navigate, 0, false, false, Restore);

    (void)hwnd;
}

void drawSectionHeading(HDC dc, int x, int y, int width, const std::wstring& title, const std::wstring& subtitle, const std::wstring& tag = L"") {
    drawHeading(dc, MulDiv(x, 96, gDpi), MulDiv(y, 96, gDpi), MulDiv(width, 96, gDpi), title, subtitle, tag);
}

void drawToggle(HDC dc, RECT rect, bool value, Action action, int index, bool disabled = false) {
    addTarget(rect, action, index, 0, disabled);
    const int targetIndex = static_cast<int>(gTargets.size()) - 1;
    const bool hovered = targetIndex == gHoveredTarget;
    COLORREF fill = value ? RGB(43, 64, 39) : RGB(38, 47, 59);
    COLORREF border = value ? RGB(98, 137, 62) : RGB(59, 71, 86);
    if (hovered) border = value ? kColors.lime : RGB(109, 127, 147);
    drawRoundRect(dc, rect, fill, border, 10);
    const int diameter = rect.bottom - rect.top - px(4);
    const int left = value ? rect.right - diameter - px(2) : rect.left + px(2);
    RECT knob{left, rect.top + px(2), left + diameter, rect.bottom - px(2)};
    HBRUSH brush = CreateSolidBrush(value ? kColors.lime : RGB(148, 160, 176));
    HPEN pen = CreatePen(PS_SOLID, 1, value ? kColors.lime : RGB(148, 160, 176));
    HGDIOBJ oldBrush = SelectObject(dc, brush);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    Ellipse(dc, knob.left, knob.top, knob.right, knob.bottom);
    SelectObject(dc, oldBrush); SelectObject(dc, oldPen);
    DeleteObject(brush); DeleteObject(pen);
}

void drawPageTitle(HDC dc, const std::wstring& title, const std::wstring& subtitle, const std::wstring& tag = L"") {
    RECT client{};
    if (gMainWindow) GetClientRect(gMainWindow, &client);
    const int x = px(270);
    const int right = client.right - px(28);
    drawSectionHeading(dc, x, px(79), right - x, title, subtitle, tag);
}

void drawCleanerPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Windows Cleaner", L"Sample category sizes only · nothing is scanned or deleted in this preview", L"PREVIEW ONLY");
    const int x = px(270), right = client.right - px(28), width = right - x;
    RECT summary{x, px(149), right, px(222)};
    drawRoundRect(dc, summary, RGB(18, 28, 29), RGB(47, 70, 49), 11);
    drawText(dc, L"Review every category before cleaning", RECT{x + px(15), summary.top + px(11), right - px(220), summary.top + px(32)}, kColors.text, 11, FW_SEMIBOLD);
    drawText(dc, L"Review-sensitive locations are unchecked by default. This page does not access files.", RECT{x + px(15), summary.top + px(37), right - px(220), summary.bottom - px(9)}, kColors.muted, 8, FW_NORMAL);
    int sumMb = 0;
    int selectedMb = 0;
    for (const auto& item : gCleanerItems) { sumMb += item.sampleMb; if (item.selected) selectedMb += item.sampleMb; }
    const std::wstring found = formatSampleMb(sumMb);
    const std::wstring selected = formatSampleMb(selectedMb);
    drawText(dc, found + L" found · sample", RECT{right - px(214), summary.top + px(13), right - px(15), summary.top + px(34)}, kColors.lime, 10, FW_SEMIBOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, selected + L" selected for review", RECT{right - px(214), summary.top + px(39), right - px(15), summary.bottom - px(9)}, kColors.muted, 8, FW_NORMAL, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

    drawText(dc, L"CLEANUP CATEGORIES", RECT{x, px(232), x + px(260), px(252)}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"14 sample categories · safe items preselected", RECT{right - px(280), px(232), right, px(252)}, kColors.muted, 7, FW_NORMAL, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    const int gap = px(12);
    const int colWidth = (width - gap) / 2;
    const int rowHeight = px(35);
    const int top = px(257);
    for (size_t i = 0; i < gCleanerItems.size(); ++i) {
        const int col = static_cast<int>(i / 7);
        const int row = static_cast<int>(i % 7);
        const int left = x + col * (colWidth + gap);
        RECT item{left, top + row * rowHeight, left + colWidth, top + row * rowHeight + px(31)};
        drawRoundRect(dc, item, gCleanerItems[i].selected ? RGB(19, 28, 29) : kColors.surface, gCleanerItems[i].selected ? RGB(55, 79, 52) : kColors.border, 7);
        RECT check{item.left + px(8), item.top + px(8), item.left + px(22), item.top + px(22)};
        drawRoundRect(dc, check, gCleanerItems[i].selected ? kColors.lime : RGB(20, 27, 36), gCleanerItems[i].selected ? kColors.lime : RGB(76, 89, 106), 4);
        if (gCleanerItems[i].selected) drawText(dc, L"✓", check, RGB(19, 25, 15), 8, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        drawText(dc, gCleanerItems[i].name, RECT{item.left + px(29), item.top + px(1), item.right - px(91), item.bottom - px(1)}, kColors.text, 8, FW_SEMIBOLD);
        drawText(dc, gCleanerItems[i].size, RECT{item.right - px(88), item.top + px(1), item.right - px(44), item.bottom - px(1)}, RGB(187, 198, 210), 7, FW_NORMAL, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
        drawText(dc, gCleanerItems[i].lowRisk ? L"LOW RISK" : L"REVIEW", RECT{item.right - px(43), item.top + px(1), item.right - px(5), item.bottom - px(1)}, gCleanerItems[i].lowRisk ? kColors.lime : kColors.orange, 6, FW_SEMIBOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
        addTarget(item, Action::CleanerToggle, static_cast<int>(i));
    }
    const int actionsY = top + 7 * rowHeight + px(3);
    RECT safeBtn = makeRect(0, 0, 145, 30); OffsetRect(&safeBtn, x, actionsY);
    drawButton(dc, safeBtn, L"Select safe items", Action::CleanerSelectSafe, 0, false);
    RECT reviewBtn = makeRect(0, 0, 174, 30); OffsetRect(&reviewBtn, x + px(155), actionsY);
    drawButton(dc, reviewBtn, L"Review selected items", Action::CleanerReview, 0, true);
    drawText(dc, L"Review first: logs, update files, app caches, Defender history, and Recycle Bin may be needed.", RECT{x + px(347), actionsY, right, actionsY + px(30)}, kColors.muted, 7, FW_NORMAL);
}

void drawProfileCard(HDC dc, RECT rect, const std::wstring& title, const std::wstring& desc, int index, bool selected) {
    drawRoundRect(dc, rect, selected ? RGB(24, 37, 30) : kColors.surface, selected ? RGB(93, 133, 56) : kColors.border, 9);
    RECT mark{rect.right - px(23), rect.top + px(8), rect.right - px(12), rect.top + px(19)};
    drawRoundRect(dc, mark, selected ? kColors.lime : kColors.surfaceRaised, selected ? kColors.lime : kColors.border, 6);
    drawText(dc, selected ? L"✓" : L"", mark, RGB(17, 23, 12), 6, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawText(dc, title, RECT{rect.left + px(12), rect.top + px(10), rect.right - px(28), rect.top + px(31)}, kColors.text, 9, FW_SEMIBOLD);
    drawText(dc, desc, RECT{rect.left + px(12), rect.top + px(35), rect.right - px(10), rect.bottom - px(8)}, kColors.muted, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_TOP);
    addTarget(rect, Action::GamingProfile, index);
}

void drawToggleRow(HDC dc, RECT rect, const std::wstring& title, const std::wstring& detail, bool value, Action action, int index) {
    drawRoundRect(dc, rect, kColors.surface, kColors.border, 8);
    drawText(dc, title, RECT{rect.left + px(11), rect.top + px(6), rect.right - px(57), rect.top + px(22)}, kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, detail, RECT{rect.left + px(11), rect.top + px(22), rect.right - px(58), rect.bottom - px(4)}, kColors.muted, 6, FW_NORMAL);
    RECT toggle{rect.right - px(43), rect.top + (rect.bottom - rect.top - px(18)) / 2, rect.right - px(11), rect.top + (rect.bottom - rect.top - px(18)) / 2 + px(18)};
    drawToggle(dc, toggle, value, action, index);
}

void drawGamingPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Gaming Optimizer", L"Reversible-looking profiles · switches below change sample UI state only", L"SAFETY FIRST");
    const int x = px(270), right = client.right - px(28), width = right - x;
    drawText(dc, L"OPTIMIZATION PROFILES", RECT{x, px(146), x + px(240), px(164)}, kColors.muted, 7, FW_SEMIBOLD);
    const wchar_t* names[] = {L"Safe", L"Gaming", L"Minecraft PvP", L"Maximum Performance", L"Editing", L"Custom"};
    const wchar_t* descriptions[] = {L"Conservative, reversible checks", L"Review play-session settings", L"Minecraft competitive baseline", L"Aggressive · review carefully", L"Keep creator apps responsive", L"Choose individual controls"};
    const int gap = px(9), cardW = (width - gap * 2) / 3, cardH = px(64), cardTop = px(167);
    for (int i = 0; i < 6; ++i) {
        const int col = i % 3, row = i / 3;
        RECT card{x + col * (cardW + gap), cardTop + row * (cardH + px(7)), x + col * (cardW + gap) + cardW, cardTop + row * (cardH + px(7)) + cardH};
        drawProfileCard(dc, card, names[i], descriptions[i], i, gProfile == i);
    }
    const int panelTop = px(313);
    const int leftWidth = width * 54 / 100;
    RECT checklist{x, panelTop, x + leftWidth, panelTop + px(251)};
    RECT settings{checklist.right + gap, panelTop, right, panelTop + px(251)};
    drawCard(dc, checklist, L"Profile checklist", L"Review each setting before a real native build applies it.");
    const wchar_t* checkLabels[] = {L"Game Mode", L"HAGS support check", L"Fullscreen behavior", L"Background capture", L"Power plan review"};
    for (int i = 0; i < 5; ++i) {
        RECT row{checklist.left + px(15), checklist.top + px(62 + i * 31), checklist.right - px(15), checklist.top + px(88 + i * 31)};
        drawText(dc, L"✓", RECT{row.left, row.top, row.left + px(18), row.bottom}, kColors.lime, 9, FW_BOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        drawText(dc, checkLabels[i], RECT{row.left + px(23), row.top, row.right - px(3), row.bottom}, RGB(198, 208, 220), 8, FW_NORMAL);
        if (i < 4) line(dc, row.left + px(22), row.bottom + px(2), row.right, row.bottom + px(2), RGB(31, 40, 51));
    }
    RECT apply = makeRect(0, 0, 144, 29); OffsetRect(&apply, checklist.left + px(15), checklist.bottom - px(43));
    drawButton(dc, apply, L"Preview profile", Action::Optimize, 0, true);

    drawCard(dc, settings, L"Windows gaming settings", L"Example switch states · not read from Windows");
    for (int i = 0; i < static_cast<int>(gGamingToggles.size()); ++i) {
        RECT row{settings.left + px(13), settings.top + px(58 + i * 35), settings.right - px(13), settings.top + px(89 + i * 35)};
        drawToggleRow(dc, row, gGamingToggles[static_cast<size_t>(i)].label, gGamingToggles[static_cast<size_t>(i)].detail,
            gGamingToggles[static_cast<size_t>(i)].enabled, Action::GamingToggle, i);
    }
    drawText(dc, L"This preview never edits Game Mode, HAGS, Game Bar, power plans, or capture settings.", RECT{x, panelTop + px(261), right, panelTop + px(285)}, kColors.orange, 7, FW_NORMAL);
}

void drawMinecraftPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Minecraft Optimizer", L"Launcher examples, Java guidance, and a sensible RAM baseline for a modest gaming PC", L"PRIMARY FOCUS");
    const int x = px(270), right = client.right - px(28), width = right - x, gap = px(12);
    RECT hero{x, px(149), right, px(205)};
    drawRoundRect(dc, hero, RGB(26, 23, 37), RGB(68, 55, 92), 11);
    drawText(dc, L"A smoother session starts with a sensible baseline.", RECT{x + px(15), hero.top + px(9), right - px(14), hero.top + px(29)}, RGB(234, 223, 255), 10, FW_SEMIBOLD);
    drawText(dc, L"Example target: Core i5-7500 · GTX 1050 Ti · 16 GB RAM · no launcher scan is performed", RECT{x + px(15), hero.top + px(31), right - px(14), hero.bottom - px(7)}, kColors.muted, 7, FW_NORMAL);

    const int top = px(218), leftWidth = width * 57 / 100;
    RECT launchers{x, top, x + leftWidth, top + px(206)};
    RECT runtime{launchers.right + gap, top, right, top + px(206)};
    drawCard(dc, launchers, L"Launcher availability", L"Example results only · not scanned from this device");
    const wchar_t* launcherNames[] = {L"Minecraft Launcher", L"Prism Launcher", L"Feather", L"Lunar Client", L"Badlion Client", L"TLauncher"};
    for (int i = 0; i < 6; ++i) {
        const int col = i / 3, row = i % 3;
        const int cellW = (leftWidth - px(42)) / 2;
        RECT cell{launchers.left + px(14) + col * (cellW + px(12)), launchers.top + px(62) + row * px(40), launchers.left + px(14) + col * (cellW + px(12)) + cellW, launchers.top + px(94) + row * px(40)};
        drawRoundRect(dc, cell, RGB(15, 21, 30), kColors.border, 7);
        drawText(dc, launcherNames[i], RECT{cell.left + px(8), cell.top + px(2), cell.right - px(46), cell.bottom - px(2)}, kColors.text, 7, FW_SEMIBOLD);
        drawText(dc, i < 3 ? L"SAMPLE" : L"—", RECT{cell.right - px(45), cell.top + px(2), cell.right - px(7), cell.bottom - px(2)}, i < 3 ? kColors.lime : kColors.dim, 6, FW_SEMIBOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    }
    RECT recheck = makeRect(0, 0, 149, 27); OffsetRect(&recheck, launchers.left + px(14), launchers.bottom - px(37));
    drawButton(dc, recheck, L"Recheck launchers", Action::MinecraftRescan, 0, false);

    drawCard(dc, runtime, L"Java runtime guidance", L"Confirm runtime within your launcher");
    drawText(dc, L"Suggested for modern Minecraft", RECT{runtime.left + px(14), runtime.top + px(63), runtime.right - px(12), runtime.top + px(81)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"Java 21 · 1.20.5+", RECT{runtime.left + px(14), runtime.top + px(81), runtime.right - px(12), runtime.top + px(104)}, kColors.text, 10, FW_SEMIBOLD);
    drawText(dc, L"Older versions may use Java 17 or Java 8; check the exact version and mod loader.", RECT{runtime.left + px(14), runtime.top + px(111), runtime.right - px(12), runtime.top + px(151)}, kColors.muted, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_TOP);
    drawText(dc, L"Installed Java: not detected", RECT{runtime.left + px(14), runtime.top + px(166), runtime.right - px(12), runtime.top + px(186)}, kColors.orange, 7, FW_SEMIBOLD);

    const int memoryTop = top + px(219);
    const int memoryH = px(170);
    RECT memory{x, memoryTop, x + leftWidth, memoryTop + memoryH};
    RECT presets{memory.right + gap, memoryTop, right, memoryTop + memoryH};
    drawCard(dc, memory, L"Memory allocation", L"Leave headroom for Windows, mods, shaders, and recording.");
    drawText(dc, L"Maximum heap", RECT{memory.left + px(15), memory.top + px(63), memory.left + px(150), memory.top + px(85)}, kColors.muted, 8, FW_NORMAL);
    drawText(dc, std::to_wstring(gMinecraftRam) + L" GB", RECT{memory.right - px(100), memory.top + px(58), memory.right - px(16), memory.top + px(87)}, kColors.purple, 15, FW_BOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    RECT minus = makeRect(0, 0, 30, 27); OffsetRect(&minus, memory.left + px(15), memory.top + px(94));
    RECT plus = makeRect(0, 0, 30, 27); OffsetRect(&plus, memory.left + px(54), memory.top + px(94));
    drawButton(dc, minus, L"−", Action::RamDown, 0, false, gMinecraftRam <= 2);
    drawButton(dc, plus, L"+", Action::RamUp, 0, false, gMinecraftRam >= 10);
    drawText(dc, L"Suggested range for this 16 GB example: 6–8 GB", RECT{memory.left + px(99), memory.top + px(92), memory.right - px(11), memory.top + px(125)}, kColors.muted, 7, FW_NORMAL);
    RECT balanced = makeRect(0, 0, 70, 24); OffsetRect(&balanced, memory.left + px(14), memory.top + px(134));
    RECT minimal = makeRect(0, 0, 66, 24); OffsetRect(&minimal, memory.left + px(90), memory.top + px(134));
    drawButton(dc, balanced, L"Balanced", Action::JvmPreset, 0, gJvmPreset == 0);
    drawButton(dc, minimal, L"Minimal", Action::JvmPreset, 1, gJvmPreset == 1);
    std::wstring jvmArgs = L"-Xms2G -Xmx" + std::to_wstring(gMinecraftRam) + L"G -XX:+UseG1GC";
    if (gJvmPreset == 0) jvmArgs += L" -XX:MaxGCPauseMillis=50";
    drawText(dc, jvmArgs, RECT{memory.left + px(165), memory.top + px(132), memory.right - px(10), memory.top + px(159)}, RGB(166, 204, 150), 6, FW_NORMAL, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    drawCard(dc, presets, L"Play profiles", L"Choose a recommendation for this preview");
    const wchar_t* profiles[] = {L"PvP", L"Smooth FPS", L"Shaders", L"Recording"};
    const wchar_t* profileDesc[] = {L"Low overhead", L"Steady frame pacing", L"Check GPU + VRAM", L"Leave capture headroom"};
    for (int i = 0; i < 4; ++i) {
        RECT item{presets.left + px(13), presets.top + px(59 + i * 26), presets.right - px(13), presets.top + px(81 + i * 26)};
        drawRoundRect(dc, item, i == gMinecraftProfile ? RGB(30, 29, 42) : RGB(15, 21, 30), i == gMinecraftProfile ? RGB(91, 70, 126) : kColors.border, 6);
        drawText(dc, profiles[i], RECT{item.left + px(8), item.top, item.left + px(94), item.bottom}, i == gMinecraftProfile ? kColors.purple : kColors.text, 7, FW_SEMIBOLD);
        drawText(dc, profileDesc[i], RECT{item.left + px(90), item.top, item.right - px(7), item.bottom}, kColors.muted, 6, FW_NORMAL, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
        addTarget(item, Action::MinecraftProfile, i);
    }
    RECT process{ x, memory.bottom + px(10), right, memory.bottom + px(77) };
    drawRoundRect(dc, process, kColors.surface, kColors.border, 9);
    drawText(dc, L"PROCESS & BACKGROUND REVIEW", RECT{process.left + px(13), process.top + px(7), process.right - px(10), process.top + px(21)}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"Normal priority is safest · close only apps you recognize", RECT{process.left + px(13), process.top + px(24), process.right - px(340), process.bottom - px(6)}, kColors.text, 7, FW_NORMAL);
    RECT priority = makeRect(0, 0, 135, 25); OffsetRect(&priority, process.right - px(290), process.top + px(30));
    RECT background = makeRect(0, 0, 140, 25); OffsetRect(&background, process.right - px(150), process.top + px(30));
    drawButton(dc, priority, L"Priority review", Action::ProcessReview, 0, false);
    drawButton(dc, background, L"Background review", Action::BackgroundReview, 0, false);
}

void drawNetworkPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Network Optimizer", L"Benchmark before considering changes · no blind TCP tuning or registry edits", L"NO BLIND TUNING");
    const int x = px(270), right = client.right - px(28), width = right - x, gap = px(12);
    const int leftW = width * 56 / 100, top = px(151);
    RECT latency{x, top, x + leftW, top + px(204)};
    RECT dns{latency.right + gap, top, right, top + px(204)};
    drawCard(dc, latency, L"Latency lab", L"No packets are sent by this preview");
    const wchar_t* labels[] = {L"Latency", L"Jitter", L"Packet loss"};
    const wchar_t* values[] = {L"Not tested", L"Not tested", L"Not tested"};
    const int statGap = px(8), statW = (leftW - px(40)) / 3;
    for (int i = 0; i < 3; ++i) {
        RECT stat{latency.left + px(14) + i * (statW + statGap), latency.top + px(64), latency.left + px(14) + i * (statW + statGap) + statW, latency.top + px(117)};
        drawRoundRect(dc, stat, RGB(13, 19, 27), kColors.border, 7);
        drawText(dc, labels[i], RECT{stat.left + px(8), stat.top + px(5), stat.right - px(8), stat.top + px(20)}, kColors.muted, 6, FW_NORMAL);
        drawText(dc, values[i], RECT{stat.left + px(8), stat.top + px(22), stat.right - px(8), stat.bottom - px(4)}, kColors.text, 8, FW_SEMIBOLD);
    }
    RECT benchmark = makeRect(0, 0, 150, 29); OffsetRect(&benchmark, latency.left + px(14), latency.top + px(132));
    drawButton(dc, benchmark, gTaskMode == TaskMode::NetworkTest && gTaskProgress < 100 ? L"Testing…" : L"Run sample test", Action::NetworkTest, 0, true, gTaskMode != TaskMode::None && gTaskProgress < 100);
    drawText(dc, L"Real ping / packet-loss integration not connected", RECT{latency.left + px(176), latency.top + px(132), latency.right - px(10), latency.top + px(161)}, kColors.muted, 7, FW_NORMAL);
    if (gTaskMode == TaskMode::NetworkTest) {
        RECT bar{latency.left + px(14), latency.bottom - px(20), latency.right - px(14), latency.bottom - px(14)};
        drawProgress(dc, bar, gTaskProgress, kColors.blue);
    }

    drawCard(dc, dns, L"DNS profile", L"Select a provider for review; nothing is applied");
    const wchar_t* dnsNames[] = {L"Cloudflare · 1.1.1.1", L"Google DNS · 8.8.8.8", L"Quad9 · 9.9.9.9"};
    for (int i = 0; i < 3; ++i) {
        RECT option{dns.left + px(14), dns.top + px(62 + i * 34), dns.right - px(14), dns.top + px(91 + i * 34)};
        drawRoundRect(dc, option, i == gDnsProfile ? RGB(18, 27, 39) : RGB(14, 20, 28), i == gDnsProfile ? RGB(60, 80, 115) : kColors.border, 7);
        drawText(dc, dnsNames[i], RECT{option.left + px(10), option.top + px(1), option.right - px(9), option.bottom - px(1)}, i == gDnsProfile ? kColors.blue : kColors.text, 8, FW_SEMIBOLD);
        addTarget(option, Action::DnsChoice, i);
    }
    drawText(dc, L"DNS changes do not guarantee lower game latency.", RECT{dns.left + px(14), dns.bottom - px(20), dns.right - px(10), dns.bottom - px(5)}, kColors.muted, 7, FW_NORMAL);

    RECT adapter{x, top + px(218), right, top + px(366)};
    drawCard(dc, adapter, L"Adapter & advanced review", L"Read-only example information · adapter values are not enumerated here");
    drawText(dc, L"Adapter", RECT{x + px(14), adapter.top + px(60), x + px(120), adapter.top + px(80)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"Not queried", RECT{x + px(125), adapter.top + px(60), x + px(300), adapter.top + px(80)}, kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, L"MTU / power saving", RECT{x + px(14), adapter.top + px(85), x + px(160), adapter.top + px(105)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"Check Windows adapter settings", RECT{x + px(165), adapter.top + px(85), x + px(430), adapter.top + px(105)}, kColors.text, 8, FW_SEMIBOLD);
    RECT reset = makeRect(0, 0, 170, 28); OffsetRect(&reset, x + px(14), adapter.top + px(110));
    RECT gaming = makeRect(0, 0, 178, 28); OffsetRect(&gaming, x + px(194), adapter.top + px(110));
    drawButton(dc, reset, L"Review reset risks", Action::NetworkAdvanced, 0, false);
    drawButton(dc, gaming, L"Gaming profile review", Action::NetworkAdvanced, 1, false);
    drawText(dc, L"TCP registry tuning is not included.", RECT{x + px(388), adapter.top + px(111), right - px(10), adapter.top + px(136)}, kColors.orange, 7, FW_NORMAL);
}

void drawHardwarePage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Hardware & BIOS Advisor", L"Read-only local information where available · firmware changes are never automated", L"ADVISORY ONLY");
    const int x = px(270), right = client.right - px(28), width = right - x;
    const wchar_t* tabs[] = {L"CPU", L"GPU", L"BIOS"};
    int tabX = x;
    for (int i = 0; i < 3; ++i) {
        RECT tab = makeRect(0, 0, 93, 28); OffsetRect(&tab, tabX, px(145));
        drawRoundRect(dc, tab, gHardwareTab == i ? RGB(30, 42, 34) : kColors.surface, gHardwareTab == i ? RGB(66, 93, 52) : kColors.border, 7);
        drawText(dc, tabs[i], tab, gHardwareTab == i ? kColors.lime : kColors.muted, 8, FW_SEMIBOLD, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        addTarget(tab, Action::HardwareTab, i);
        tabX += px(100);
    }
    RECT main{x, px(185), right, px(446)};
    drawRoundRect(dc, main, kColors.surface, kColors.border, 12);
    if (gHardwareTab == 0) {
        drawText(dc, L"CPU · read-only", RECT{x + px(17), main.top + px(15), right - px(15), main.top + px(35)}, kColors.text, 12, FW_SEMIBOLD);
        drawText(dc, gMetrics.processorName.empty() ? L"Processor name unavailable" : gMetrics.processorName, RECT{x + px(17), main.top + px(43), right - px(17), main.top + px(73)}, kColors.blue, 12, FW_SEMIBOLD);
        const DWORD processors = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
        const std::vector<std::pair<std::wstring, std::wstring>> values = {
            {L"Logical processors", std::to_wstring(processors)},
            {L"CPU usage", gMetrics.cpuReady ? std::to_wstring(static_cast<int>(gMetrics.cpuPercent + 0.5)) + L"%" : L"Measuring"},
            {L"Installed memory", gMetrics.memoryTotal ? formatBytes(gMetrics.memoryTotal) : L"Unavailable"},
            {L"Available memory", gMetrics.memoryAvailable ? formatBytes(gMetrics.memoryAvailable) : L"Unavailable"},
        };
        for (size_t i = 0; i < values.size(); ++i) {
            const int col = static_cast<int>(i % 2), row = static_cast<int>(i / 2);
            RECT tile{x + px(16) + col * (width / 2 - px(18)), main.top + px(91) + row * px(59), x + px(16) + col * (width / 2 - px(18)) + width / 2 - px(30), main.top + px(140) + row * px(59)};
            drawRoundRect(dc, tile, RGB(13, 19, 27), kColors.border, 8);
            drawText(dc, values[i].first, RECT{tile.left + px(9), tile.top + px(3), tile.right - px(7), tile.top + px(18)}, kColors.muted, 7, FW_NORMAL);
            drawText(dc, values[i].second, RECT{tile.left + px(9), tile.top + px(20), tile.right - px(7), tile.bottom - px(3)}, kColors.text, 10, FW_SEMIBOLD);
        }
        drawText(dc, L"Power plan changes are not applied. Compare temperatures, clocks, and workload before tuning.", RECT{x + px(17), main.bottom - px(31), right - px(17), main.bottom - px(10)}, kColors.muted, 7, FW_NORMAL);
    } else if (gHardwareTab == 1) {
        drawText(dc, L"GPU · display adapter", RECT{x + px(17), main.top + px(15), right - px(15), main.top + px(35)}, kColors.text, 12, FW_SEMIBOLD);
        drawText(dc, gMetrics.graphicsName.empty() ? L"Graphics adapter unavailable" : gMetrics.graphicsName, RECT{x + px(17), main.top + px(45), right - px(17), main.top + px(77)}, kColors.orange, 11, FW_SEMIBOLD);
        const std::vector<std::pair<std::wstring, std::wstring>> rows = {
            {L"Usage telemetry", L"Not connected"}, {L"Driver version", L"Not queried"},
            {L"GPU scheduling", L"Check Windows + driver support"}, {L"Shader cache", L"Review in GPU vendor settings"},
            {L"Per-game profile", L"Manual review only"}, {L"Background GPU apps", L"Use Task Manager to inspect"},
        };
        for (size_t i = 0; i < rows.size(); ++i) {
            const int rowY = main.top + px(94) + static_cast<int>(i) * px(27);
            drawText(dc, rows[i].first, RECT{x + px(18), rowY, x + px(238), rowY + px(20)}, kColors.muted, 8, FW_NORMAL);
            drawText(dc, rows[i].second, RECT{x + px(242), rowY, right - px(18), rowY + px(20)}, kColors.text, 8, FW_SEMIBOLD);
        }
    } else {
        drawText(dc, L"BIOS Advisor · no firmware changes", RECT{x + px(17), main.top + px(15), right - px(15), main.top + px(35)}, kColors.text, 12, FW_SEMIBOLD);
        const std::vector<std::pair<std::wstring, std::wstring>> rows = {
            {L"CPU virtualization", L"Not queried"}, {L"TPM 2.0", L"Check Windows Security"},
            {L"Secure Boot", L"Check System Information"}, {L"Resizable BAR", L"Check board + GPU support"},
            {L"XMP / EXPO", L"Manual board-specific review"}, {L"Above 4G decoding", L"Firmware support varies"},
            {L"Boot mode / BIOS version", L"Not queried"}, {L"Motherboard model", L"Not queried"},
        };
        for (size_t i = 0; i < rows.size(); ++i) {
            const int rowY = main.top + px(52) + static_cast<int>(i) * px(24);
            drawText(dc, rows[i].first, RECT{x + px(18), rowY, x + px(242), rowY + px(19)}, kColors.muted, 7, FW_NORMAL);
            drawText(dc, rows[i].second, RECT{x + px(246), rowY, right - px(18), rowY + px(19)}, kColors.orange, 7, FW_SEMIBOLD);
        }
    }
    RECT warning{x, px(462), right, px(512)};
    drawRoundRect(dc, warning, RGB(34, 27, 21), RGB(76, 55, 35), 9);
    drawText(dc, L"Never flash BIOS, overclock, or enable XMP / EXPO automatically. Incorrect firmware or unstable memory settings can prevent booting.", RECT{x + px(13), warning.top + px(7), right - px(13), warning.bottom - px(7)}, kColors.orange, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
}

void drawStartupPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Startup Manager", L"Example entries only · enable / disable buttons update this sample list, not Windows", L"NO REGISTRY EDITS");
    const int x = px(270), right = client.right - px(28), width = right - x;
    int enabled = 0;
    for (const auto& item : gStartupItems) if (item.enabled) ++enabled;
    RECT summary{x, px(149), right, px(202)};
    drawRoundRect(dc, summary, kColors.surface, kColors.border, 10);
    drawText(dc, std::to_wstring(enabled) + L" enabled", RECT{x + px(14), summary.top + px(8), x + px(160), summary.bottom - px(7)}, kColors.lime, 12, FW_BOLD);
    drawText(dc, L"Sample list · 8 entries · system startup is not enumerated", RECT{x + px(172), summary.top + px(8), right - px(12), summary.bottom - px(7)}, kColors.muted, 8, FW_NORMAL);
    const int gap = px(12), colW = (width - gap) / 2, rowHeight = px(48), top = px(214);
    const wchar_t* impacts[] = {L"Medium", L"High", L"Medium", L"High", L"High", L"Low", L"Low", L"Medium"};
    for (size_t i = 0; i < gStartupItems.size(); ++i) {
        const int col = static_cast<int>(i / 4), row = static_cast<int>(i % 4);
        RECT item{x + col * (colW + gap), top + row * rowHeight, x + col * (colW + gap) + colW, top + row * rowHeight + px(42)};
        drawRoundRect(dc, item, kColors.surface, kColors.border, 8);
        drawText(dc, gStartupItems[i].name, RECT{item.left + px(10), item.top + px(3), item.right - px(125), item.top + px(20)}, kColors.text, 8, FW_SEMIBOLD);
        drawText(dc, gStartupItems[i].publisher, RECT{item.left + px(10), item.top + px(21), item.right - px(125), item.bottom - px(3)}, kColors.muted, 6, FW_NORMAL);
        drawText(dc, impacts[i], RECT{item.right - px(115), item.top + px(3), item.right - px(68), item.bottom - px(3)}, std::wstring(impacts[i]) == L"High" ? kColors.orange : kColors.blue, 7, FW_NORMAL, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        RECT toggle{item.right - px(56), item.top + px(12), item.right - px(18), item.top + px(31)};
        drawToggle(dc, toggle, gStartupItems[i].enabled, Action::StartupToggle, static_cast<int>(i));
        drawText(dc, gStartupItems[i].enabled ? L"Enabled" : L"Disabled", RECT{item.right - px(111), item.top + px(25), item.right - px(62), item.bottom - px(3)}, kColors.muted, 6, FW_NORMAL, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    }
    RECT note{x, top + px(4 * 48) + px(5), right, top + px(4 * 48) + px(48)};
    drawRoundRect(dc, note, RGB(17, 24, 33), kColors.border, 8);
    drawText(dc, L"A signed native manager must back up each Run entry / task and show the exact path before changing it.", RECT{note.left + px(12), note.top + px(5), note.right - px(12), note.bottom - px(5)}, kColors.muted, 7, FW_NORMAL);
}

void drawServicesPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Services Manager", L"Advanced read-only guidance · service dependencies vary by Windows install", L"KEEP SAFE DEFAULTS");
    const int x = px(270), right = client.right - px(28), width = right - x;
    RECT warning{x, px(149), right, px(201)};
    drawRoundRect(dc, warning, RGB(17, 25, 34), RGB(44, 59, 78), 9);
    drawText(dc, L"Do not disable Windows services at random.", RECT{x + px(13), warning.top + px(7), right - px(12), warning.top + px(24)}, kColors.blue, 8, FW_SEMIBOLD);
    drawText(dc, L"The rows below are examples, not enumerated services. This app makes no service changes.", RECT{x + px(13), warning.top + px(27), right - px(12), warning.bottom - px(5)}, kColors.muted, 7, FW_NORMAL);
    const int top = px(214), rowH = px(45);
    RECT header{x, top, right, top + px(25)};
    drawText(dc, L"SERVICE", RECT{x + px(10), header.top, x + px(275), header.bottom}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"STATE", RECT{x + px(284), header.top, x + px(390), header.bottom}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"STARTUP", RECT{x + px(403), header.top, x + px(548), header.bottom}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"GUIDANCE", RECT{x + px(565), header.top, right - px(65), header.bottom}, kColors.muted, 7, FW_SEMIBOLD);
    for (size_t i = 0; i < gServices.size(); ++i) {
        RECT row{x, top + px(27) + static_cast<int>(i) * rowH, right, top + px(27) + static_cast<int>(i) * rowH + px(40)};
        drawRoundRect(dc, row, kColors.surface, kColors.border, 7);
        drawText(dc, gServices[i].name, RECT{row.left + px(10), row.top, row.left + px(274), row.bottom}, kColors.text, 7, FW_SEMIBOLD);
        drawText(dc, gServices[i].state, RECT{row.left + px(284), row.top, row.left + px(393), row.bottom}, std::wstring(gServices[i].state) == L"Running" ? kColors.lime : kColors.muted, 7, FW_NORMAL);
        drawText(dc, gServices[i].startup, RECT{row.left + px(403), row.top, row.left + px(552), row.bottom}, kColors.muted, 7, FW_NORMAL);
        drawText(dc, gServices[i].recommendation, RECT{row.left + px(565), row.top, row.right - px(70), row.bottom}, std::wstring(gServices[i].recommendation) == L"Keep default" ? kColors.lime : kColors.orange, 7, FW_SEMIBOLD);
        RECT review = makeRect(0, 0, 54, 25); OffsetRect(&review, row.right - px(62), row.top + px(7));
        drawButton(dc, review, L"Review", Action::ServiceReview, static_cast<int>(i), false);
    }
}

void drawPrivacyPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Privacy Controls", L"Optional preferences · sample states only · no settings are changed", L"LOCAL PREVIEW");
    const int x = px(270), right = client.right - px(28), width = right - x;
    const int gap = px(12), leftW = width * 60 / 100;
    RECT list{x, px(149), x + leftW, px(456)};
    RECT note{list.right + gap, px(149), right, px(456)};
    drawCard(dc, list, L"Optional controls", L"Current values are examples, not read from Windows.");
    for (int i = 0; i < static_cast<int>(gPrivacyToggles.size()); ++i) {
        RECT row{list.left + px(13), list.top + px(61 + i * 61), list.right - px(13), list.top + px(114 + i * 61)};
        drawToggleRow(dc, row, gPrivacyToggles[static_cast<size_t>(i)].label, gPrivacyToggles[static_cast<size_t>(i)].detail,
            gPrivacyToggles[static_cast<size_t>(i)].enabled, Action::SettingsToggle, i + 100);
    }
    drawCard(dc, note, L"Before changing privacy", L"Use Windows Settings to review scope.");
    const wchar_t* bullet[] = {L"Controls may vary by Windows version.", L"Some diagnostics support updates and troubleshooting.", L"Background permission is per-app on many builds.", L"Record the old value before changing it."};
    for (int i = 0; i < 4; ++i) {
        drawText(dc, L"•", RECT{note.left + px(14), note.top + px(66 + i * 42), note.left + px(28), note.top + px(91 + i * 42)}, kColors.lime, 9, FW_BOLD);
        drawText(dc, bullet[i], RECT{note.left + px(31), note.top + px(63 + i * 42), note.right - px(12), note.top + px(94 + i * 42)}, kColors.muted, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_TOP);
    }
    RECT commitment{x, px(469), right, px(520)};
    drawRoundRect(dc, commitment, RGB(17, 25, 31), kColors.border, 9);
    drawText(dc, L"Privacy: no HWID, account, device fingerprint, telemetry service, or cloud license system is implemented in this prototype.", RECT{commitment.left + px(13), commitment.top + px(7), commitment.right - px(13), commitment.bottom - px(7)}, kColors.blue, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
}

void drawDebloatPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Debloat", L"Review optional apps individually · no bulk removal action", L"ONE APP AT A TIME");
    const int x = px(270), right = client.right - px(28), width = right - x;
    const wchar_t* names[] = {L"Clipchamp", L"Microsoft News", L"Weather", L"Teams (personal)", L"Xbox app", L"Mixed Reality Portal"};
    const wchar_t* notes[] = {L"Optional video editor · check use", L"Optional news app", L"Optional widget app", L"Keep if you use calls", L"Keep for Game Pass / Xbox", L"Optional VR component"};
    const int gap = px(10), cols = 3, rows = 2, cardW = (width - gap * (cols - 1)) / cols, cardH = px(114), top = px(151);
    for (int i = 0; i < 6; ++i) {
        const int col = i % cols, row = i / cols;
        RECT card{x + col * (cardW + gap), top + row * (cardH + gap), x + col * (cardW + gap) + cardW, top + row * (cardH + gap) + cardH};
        drawRoundRect(dc, card, kColors.surface, kColors.border, 10);
        drawText(dc, names[i], RECT{card.left + px(12), card.top + px(11), card.right - px(10), card.top + px(31)}, kColors.text, 9, FW_SEMIBOLD);
        drawText(dc, L"Microsoft · sample catalog", RECT{card.left + px(12), card.top + px(35), card.right - px(10), card.top + px(51)}, kColors.muted, 7, FW_NORMAL);
        drawText(dc, notes[i], RECT{card.left + px(12), card.top + px(54), card.right - px(10), card.top + px(75)}, kColors.muted, 7, FW_NORMAL);
        RECT button = makeRect(0, 0, 116, 25); OffsetRect(&button, card.left + px(12), card.bottom - px(35));
        drawButton(dc, button, L"Review app", Action::DebloatReview, i, false);
    }
    RECT info{x, top + 2 * (cardH + gap) + px(2), right, top + 2 * (cardH + gap) + px(52)};
    drawRoundRect(dc, info, RGB(34, 27, 21), RGB(76, 55, 35), 9);
    drawText(dc, L"No “Remove Everything” button. Verify dependencies and reinstall options before removing any package.", RECT{info.left + px(13), info.top + px(7), info.right - px(13), info.bottom - px(7)}, kColors.orange, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
}

void drawRepairPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"System Repair", L"Terminal-style progress simulation · this C++ preview runs no commands", L"SIMULATION ONLY");
    const int x = px(270), right = client.right - px(28), width = right - x;
    const wchar_t* names[] = {L"System File Checker", L"DISM image repair", L"Disk check", L"Windows Update repair", L"Network repair", L"Component Store check"};
    const wchar_t* desc[] = {L"Check protected Windows files", L"Review the component image", L"File-system health check", L"Guided update troubleshooting", L"Review connection issues", L"Check component-store health"};
    const int gap = px(9), cardW = (width - gap * 2) / 3, cardH = px(87), top = px(151);
    for (int i = 0; i < 6; ++i) {
        const int col = i % 3, row = i / 3;
        RECT card{x + col * (cardW + gap), top + row * (cardH + gap), x + col * (cardW + gap) + cardW, top + row * (cardH + gap) + cardH};
        drawRoundRect(dc, card, kColors.surface, kColors.border, 9);
        drawText(dc, names[i], RECT{card.left + px(11), card.top + px(8), card.right - px(10), card.top + px(27)}, kColors.text, 8, FW_SEMIBOLD);
        drawText(dc, desc[i], RECT{card.left + px(11), card.top + px(30), card.right - px(10), card.top + px(48)}, kColors.muted, 7, FW_NORMAL);
        RECT btn = makeRect(0, 0, 95, 24); OffsetRect(&btn, card.left + px(11), card.bottom - px(31));
        drawButton(dc, btn, L"Preview run", Action::RepairRun, i, false, gTaskMode != TaskMode::None && gTaskProgress < 100);
    }
    const int consoleTop = top + 2 * (cardH + gap) + px(6);
    RECT console{x, consoleTop, right, consoleTop + px(150)};
    drawRoundRect(dc, console, RGB(7, 11, 16), RGB(38, 50, 65), 10);
    drawText(dc, L"THARU SYSTEM REPAIR · PREVIEW CONSOLE", RECT{x + px(13), console.top + px(9), right - px(13), console.top + px(27)}, kColors.muted, 7, FW_SEMIBOLD);
    drawText(dc, L"> No system commands have been executed.", RECT{x + px(14), console.top + px(39), right - px(14), console.top + px(58)}, RGB(160, 190, 140), 8, FW_NORMAL);
    drawText(dc, gTaskMode == TaskMode::Repair ? gTaskLabel : L"> Choose a diagnostic to preview its progress flow.", RECT{x + px(14), console.top + px(62), right - px(14), console.top + px(83)}, RGB(160, 190, 140), 8, FW_NORMAL);
    if (gTaskMode == TaskMode::Repair && gTaskProgress < 100) {
        RECT bar{x + px(14), console.top + px(104), right - px(14), console.top + px(112)};
        drawProgress(dc, bar, gTaskProgress, kColors.lime);
        drawText(dc, std::to_wstring(gTaskProgress) + L"%", RECT{right - px(55), console.top + px(116), right - px(14), console.top + px(133)}, kColors.muted, 7, FW_NORMAL, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    } else {
        drawText(dc, gTaskMode == TaskMode::Repair ? L"Preview complete · no files or system components modified." : L"SFC / DISM / CHKDSK are not invoked by this preview.", RECT{x + px(14), console.top + px(105), right - px(14), console.top + px(126)}, kColors.muted, 7, FW_NORMAL);
    }
}

void drawRestorePage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Restore Center", L"Safety workflow for a future native build · no actual restore point has been created", L"NO SYSTEM CHANGES");
    const int x = px(270), right = client.right - px(28), width = right - x, gap = px(12), top = px(151);
    RECT banner{x, top, right, top + px(89)};
    drawRoundRect(dc, banner, RGB(19, 29, 27), RGB(51, 76, 47), 11);
    drawText(dc, L"Build a safety net before tuning.", RECT{x + px(15), banner.top + px(13), right - px(15), banner.top + px(33)}, kColors.text, 10, FW_SEMIBOLD);
    drawText(dc, L"Real System Restore, registry exports, and file backups require Windows integration and elevated permission.", RECT{x + px(15), banner.top + px(38), right - px(220), banner.bottom - px(9)}, kColors.muted, 7, FW_NORMAL);
    RECT create = makeRect(0, 0, 164, 30); OffsetRect(&create, right - px(179), banner.top + px(28));
    drawButton(dc, create, L"Create restore point", Action::CreateRestore, 0, true);

    const int leftW = width * 58 / 100;
    RECT snapshots{x, top + px(101), x + leftW, top + px(342)};
    RECT flow{snapshots.right + gap, snapshots.top, right, snapshots.bottom};
    drawCard(dc, snapshots, L"Preview snapshots", L"Browser session records only · not Windows restore points");
    drawText(dc, L"Preview session started", RECT{snapshots.left + px(15), snapshots.top + px(66), snapshots.right - px(15), snapshots.top + px(87)}, kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, L"Local in-memory record · this session", RECT{snapshots.left + px(15), snapshots.top + px(88), snapshots.right - px(15), snapshots.top + px(105)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"No optimizer changes have been applied.", RECT{snapshots.left + px(15), snapshots.top + px(122), snapshots.right - px(15), snapshots.top + px(145)}, kColors.lime, 8, FW_SEMIBOLD);
    RECT undo = makeRect(0, 0, 149, 28); OffsetRect(&undo, snapshots.left + px(15), snapshots.bottom - px(43));
    drawButton(dc, undo, L"Undo preview run", Action::Undo, 0, false);
    RECT exportBtn = makeRect(0, 0, 157, 28); OffsetRect(&exportBtn, snapshots.left + px(175), snapshots.bottom - px(43));
    drawButton(dc, exportBtn, L"Export preview JSON", Action::ExportPreview, 0, false);

    drawCard(dc, flow, L"Safe change sequence", L"Recommended for a signed native Windows version");
    const wchar_t* steps[] = {L"1. Create and verify a restore point", L"2. Export exact values before change", L"3. Apply one reversible action", L"4. Confirm result and offer Undo"};
    for (int i = 0; i < 4; ++i) drawText(dc, steps[i], RECT{flow.left + px(14), flow.top + px(67 + i * 37), flow.right - px(12), flow.top + px(89 + i * 37)}, kColors.text, 7, FW_NORMAL);

    RECT note{x, top + px(354), right, top + px(403)};
    drawRoundRect(dc, note, RGB(33, 28, 22), RGB(72, 56, 37), 9);
    drawText(dc, L"The current app has no registry backup, system restore integration, or system settings to undo.", RECT{note.left + px(13), note.top + px(5), note.right - px(13), note.bottom - px(5)}, kColors.orange, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
}

void drawSettingsPage(HDC dc, RECT client) {
    drawPageTitle(dc, L"Settings", L"Local preview preferences and implementation status", L"OFFLINE PREVIEW");
    const int x = px(270), right = client.right - px(28), width = right - x, gap = px(12), leftW = width * 60 / 100, top = px(151);
    RECT pref{x, top, x + leftW, top + px(262)};
    RECT info{pref.right + gap, top, right, top + px(262)};
    drawCard(dc, pref, L"Preferences", L"Switches below only update this window's sample state.");
    const wchar_t* prefNames[] = {L"In-app notifications", L"Launch on sign-in", L"Compact dashboard"};
    const wchar_t* prefDetails[] = {L"Show brief status feedback", L"Not connected to Windows startup", L"Changes are not persisted"};
    for (int i = 0; i < 3; ++i) {
        RECT row{pref.left + px(13), pref.top + px(64 + i * 51), pref.right - px(13), pref.top + px(107 + i * 51)};
        drawToggleRow(dc, row, prefNames[i], prefDetails[i], gSettingsPrefs[i], Action::SettingsToggle, i);
    }
    drawCard(dc, info, L"About THARU OPTIMIZER", L"Version 0.1.0 · native Win32 preview");
    drawText(dc, L"No license server or HWID binding", RECT{info.left + px(14), info.top + px(67), info.right - px(12), info.top + px(89)}, kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, L"No telemetry or crash reporting", RECT{info.left + px(14), info.top + px(98), info.right - px(12), info.top + px(120)}, kColors.text, 8, FW_SEMIBOLD);
    drawText(dc, L"No automatic update service", RECT{info.left + px(14), info.top + px(129), info.right - px(12), info.top + px(151)}, kColors.text, 8, FW_SEMIBOLD);
    RECT about = makeRect(0, 0, 112, 27); OffsetRect(&about, info.left + px(14), info.bottom - px(42));
    drawButton(dc, about, L"About preview", Action::About, 0, false);
    RECT notice{x, top + px(274), right, top + px(327)};
    drawRoundRect(dc, notice, RGB(17, 25, 31), kColors.border, 9);
    drawText(dc, L"Native integration, code signing, secure updates, license management, and restore verification are not implemented.", RECT{notice.left + px(13), notice.top + px(6), notice.right - px(13), notice.bottom - px(6)}, kColors.muted, 7, FW_NORMAL, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
}

void drawStatusBar(HDC dc, RECT client) {
    const int left = px(242);
    const int top = client.bottom - px(26);
    line(dc, left, top, client.right, top, RGB(28, 38, 50));
    drawText(dc, gStatus, RECT{left + px(28), top + px(3), client.right - px(105), client.bottom - px(2)}, kColors.muted, 7, FW_NORMAL);
    drawText(dc, L"LOCAL ONLY", RECT{client.right - px(96), top + px(3), client.right - px(23), client.bottom - px(2)}, kColors.lime, 7, FW_SEMIBOLD, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
}

void drawPage(HDC dc, RECT client, HWND hwnd) {
    switch (gPage) {
        case Overview: drawOverview(dc, client, hwnd); break;
        case Cleaner: drawCleanerPage(dc, client); break;
        case Gaming: drawGamingPage(dc, client); break;
        case Minecraft: drawMinecraftPage(dc, client); break;
        case Network: drawNetworkPage(dc, client); break;
        case Hardware: drawHardwarePage(dc, client); break;
        case Startup: drawStartupPage(dc, client); break;
        case Services: drawServicesPage(dc, client); break;
        case Privacy: drawPrivacyPage(dc, client); break;
        case Debloat: drawDebloatPage(dc, client); break;
        case Repair: drawRepairPage(dc, client); break;
        case Restore: drawRestorePage(dc, client); break;
        case Settings: drawSettingsPage(dc, client); break;
        default: drawOverview(dc, client, hwnd); break;
    }
}

void startPreviewTask(HWND hwnd, TaskMode mode, const std::wstring& label) {
    if (gTaskMode != TaskMode::None && gTaskProgress < 100) {
        gStatus = L"A preview task is already running";
        InvalidateRect(hwnd, nullptr, FALSE);
        return;
    }
    gTaskMode = mode;
    gTaskProgress = 0;
    gTaskLabel = label;
    if (mode == TaskMode::Scan) gStatus = L"Preview scan running · no file paths accessed";
    else if (mode == TaskMode::NetworkTest) gStatus = L"Sample test running · no network packets sent";
    else gStatus = L"Repair simulation running · no system commands executed";
    SetTimer(hwnd, kPreviewTimer, 35, nullptr);
    InvalidateRect(hwnd, nullptr, FALSE);
}

void showPreviewMessage(HWND hwnd, const std::wstring& title, const std::wstring& message, UINT iconType = MB_ICONINFORMATION) {
    MessageBoxW(hwnd, message.c_str(), title.c_str(), MB_OK | iconType);
}

void handleTarget(HWND hwnd, const HitTarget& target) {
    switch (target.action) {
        case Action::Navigate:
            gPage = static_cast<Page>(target.page);
            gHoveredTarget = -1;
            break;
        case Action::QuickScan:
            startPreviewTask(hwnd, TaskMode::Scan, L"Sample category review");
            break;
        case Action::Optimize:
            showPreviewMessage(hwnd, L"Optimize preview", L"This C++ preview can show local CPU, memory, and disk readings, but it does not apply optimizer settings.\n\nNo files are deleted. No registry, service, network, startup, power, or process settings are changed.\n\nA Windows-native restore point is not created by this preview.");
            break;
        case Action::CreateRestore:
            showPreviewMessage(hwnd, L"Restore point preview", L"No Windows System Restore point was created. A production build must request permission, call the Windows restore API, and verify success before any system change.", MB_ICONWARNING);
            break;
        case Action::CleanerToggle:
            if (target.value >= 0 && target.value < static_cast<int>(gCleanerItems.size())) gCleanerItems[static_cast<size_t>(target.value)].selected = !gCleanerItems[static_cast<size_t>(target.value)].selected;
            break;
        case Action::CleanerSelectSafe:
            for (auto& item : gCleanerItems) item.selected = item.lowRisk;
            gStatus = L"Low-risk categories selected for review · no files accessed";
            break;
        case Action::CleanerReview: {
            int count = 0, mb = 0;
            for (const auto& item : gCleanerItems) if (item.selected) { ++count; mb += item.sampleMb; }
            showPreviewMessage(hwnd, L"Cleanup review", L"Selected sample categories: " + std::to_wstring(count) + L"\nSample estimate: " + formatSampleMb(mb) + L"\n\nNo files were scanned or deleted. A real cleaner must re-measure paths and skip in-use or protected files.");
            break;
        }
        case Action::GamingProfile:
            gProfile = target.value;
            break;
        case Action::GamingToggle:
            if (target.value >= 0 && target.value < static_cast<int>(gGamingToggles.size())) gGamingToggles[static_cast<size_t>(target.value)].enabled = !gGamingToggles[static_cast<size_t>(target.value)].enabled;
            gStatus = L"Sample gaming switch updated in this window only";
            break;
        case Action::MinecraftProfile:
            gMinecraftProfile = target.value;
            break;
        case Action::RamDown:
            if (gMinecraftRam > 2) --gMinecraftRam;
            break;
        case Action::RamUp:
            if (gMinecraftRam < 10) ++gMinecraftRam;
            break;
        case Action::JvmPreset:
            gJvmPreset = target.value;
            break;
        case Action::MinecraftRescan:
            showPreviewMessage(hwnd, L"Launcher scan preview", L"Installed launchers and Java runtimes cannot be detected from this preview flow. A native build should scan only with clear user consent and never send paths or device identifiers to a server.");
            break;
        case Action::ProcessReview:
            showPreviewMessage(hwnd, L"Process priority guidance", L"Normal process priority is the safe default. Raising priority can make the desktop, audio, or other apps less responsive. No process priority was changed.", MB_ICONWARNING);
            break;
        case Action::BackgroundReview:
            showPreviewMessage(hwnd, L"Background process review", L"Save active work and close only apps you recognize. Do not terminate security, audio, graphics-driver, or Windows processes to chase a benchmark. No process was closed.", MB_ICONWARNING);
            break;
        case Action::NetworkTest:
            startPreviewTask(hwnd, TaskMode::NetworkTest, L"Sample latency / loss flow");
            break;
        case Action::DnsChoice:
            gDnsProfile = target.value;
            gStatus = L"DNS provider selected for preview only";
            break;
        case Action::NetworkAdvanced:
            if (target.value == 1) {
                showPreviewMessage(hwnd, L"Gaming network profile", L"Benchmark latency and packet loss to the same endpoint before changing adapter power or network settings. Do not force MTU or TCP registry values without evidence and an undo path. Nothing was changed.", MB_ICONWARNING);
            } else {
                showPreviewMessage(hwnd, L"Network reset guidance", L"Winsock and TCP/IP resets can disconnect applications and may require a restart. Benchmark first, record adapter settings, and create an undo path. No reset or registry tuning was run.", MB_ICONWARNING);
            }
            break;
        case Action::HardwareTab:
            gHardwareTab = target.value;
            break;
        case Action::StartupToggle:
            if (target.value >= 0 && target.value < static_cast<int>(gStartupItems.size())) {
                auto& item = gStartupItems[static_cast<size_t>(target.value)];
                item.enabled = !item.enabled;
                gStatus = std::wstring(L"Preview only: ") + item.name + (item.enabled ? L" marked enabled" : L" marked disabled");
            }
            break;
        case Action::ServiceReview:
            if (target.value >= 0 && target.value < static_cast<int>(gServices.size())) {
                const auto& item = gServices[static_cast<size_t>(target.value)];
                showPreviewMessage(hwnd, L"Service recommendation", std::wstring(item.name) + L"\nSample state: " + item.state + L" · " + item.startup + L"\nRecommendation: " + item.recommendation + L"\n\nService dependencies vary. This preview never disables services.", MB_ICONWARNING);
            }
            break;
        case Action::DebloatReview: {
            const wchar_t* apps[] = {L"Clipchamp", L"Microsoft News", L"Weather", L"Teams (personal)", L"Xbox app", L"Mixed Reality Portal"};
            if (target.value >= 0 && target.value < 6) showPreviewMessage(hwnd, L"Review optional app", std::wstring(apps[target.value]) + L"\n\nCheck dependencies and reinstall availability before removal. This preview does not uninstall apps.", MB_ICONWARNING);
            break;
        }
        case Action::RepairRun: {
            const wchar_t* tasks[] = {L"System File Checker", L"DISM image repair", L"Disk check", L"Windows Update repair", L"Network repair", L"Component Store check"};
            if (target.value >= 0 && target.value < 6) startPreviewTask(hwnd, TaskMode::Repair, tasks[target.value]);
            break;
        }
        case Action::Undo:
            showPreviewMessage(hwnd, L"Undo preview", L"No system changes have been applied, so there is nothing to undo. This button does not alter Windows.");
            break;
        case Action::ExportPreview:
            showPreviewMessage(hwnd, L"Export preview", L"Registry exports and Windows backups are not implemented. This preview has no system changes to export.");
            break;
        case Action::SettingsToggle:
            if (target.value >= 100 && target.value < 100 + static_cast<int>(gPrivacyToggles.size())) {
                auto& toggle = gPrivacyToggles[static_cast<size_t>(target.value - 100)];
                toggle.enabled = !toggle.enabled;
                gStatus = L"Sample privacy state updated · Windows was not changed";
            } else if (target.value >= 0 && target.value < 3) {
                gSettingsPrefs[target.value] = !gSettingsPrefs[target.value];
                gStatus = L"Local preference preview updated";
            }
            break;
        case Action::About:
            showPreviewMessage(hwnd, L"About THARU OPTIMIZER", L"Native C++ Win32 preview · version 0.1.0\n\nCPU, RAM, and C: drive metrics are read locally. The app does not send telemetry or device identifiers. Cleaner, gaming, startup, services, network, repair, and restore controls are preview-only.");
            break;
    }
    InvalidateRect(hwnd, nullptr, FALSE);
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            gDpi = static_cast<int>(GetDpiForWindow(hwnd));
            if (gDpi <= 0) gDpi = 96;
            refreshMetrics();
            SetTimer(hwnd, kMetricsTimer, 1000, nullptr);
            const BOOL useDark = TRUE;
            DwmSetWindowAttribute(hwnd, 20, &useDark, sizeof(useDark)); // DWMWA_USE_IMMERSIVE_DARK_MODE
            return 0;
        }
        case WM_GETMINMAXINFO: {
            auto* info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMinTrackSize.x = px(1024);
            info->ptMinTrackSize.y = px(780);
            return 0;
        }
        case WM_DPICHANGED: {
            gDpi = HIWORD(wParam);
            destroyFonts();
            const RECT* suggested = reinterpret_cast<const RECT*>(lParam);
            SetWindowPos(hwnd, nullptr, suggested->left, suggested->top, suggested->right - suggested->left,
                suggested->bottom - suggested->top, SWP_NOZORDER | SWP_NOACTIVATE);
            InvalidateRect(hwnd, nullptr, TRUE);
            return 0;
        }
        case WM_SIZE:
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT paint{};
            HDC targetDc = BeginPaint(hwnd, &paint);
            RECT client{};
            GetClientRect(hwnd, &client);
            HDC bufferDc = CreateCompatibleDC(targetDc);
            HBITMAP bitmap = CreateCompatibleBitmap(targetDc, client.right - client.left, client.bottom - client.top);
            HGDIOBJ oldBitmap = SelectObject(bufferDc, bitmap);
            RECT all{0, 0, client.right, client.bottom};
            fillRect(bufferDc, all, kColors.background);
            gTargets.clear();
            drawSidebar(bufferDc, client.bottom);
            drawTopbar(bufferDc, client.right);
            drawPage(bufferDc, client, hwnd);
            drawStatusBar(bufferDc, client);
            BitBlt(targetDc, 0, 0, client.right, client.bottom, bufferDc, 0, 0, SRCCOPY);
            SelectObject(bufferDc, oldBitmap);
            DeleteObject(bitmap);
            DeleteDC(bufferDc);
            EndPaint(hwnd, &paint);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (!gTrackingMouse) {
                TRACKMOUSEEVENT track{sizeof(TRACKMOUSEEVENT), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&track);
                gTrackingMouse = true;
            }
            POINT point{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            const int target = targetAt(point);
            if (target != gHoveredTarget) {
                gHoveredTarget = target;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            gTrackingMouse = false;
            gHoveredTarget = -1;
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_LBUTTONUP: {
            POINT point{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            const int target = targetAt(point);
            if (target >= 0 && static_cast<size_t>(target) < gTargets.size()) handleTarget(hwnd, gTargets[static_cast<size_t>(target)]);
            return 0;
        }
        case WM_SETCURSOR: {
            if (LOWORD(lParam) == HTCLIENT) {
                POINT point{};
                GetCursorPos(&point);
                ScreenToClient(hwnd, &point);
                if (targetAt(point) >= 0) {
                    SetCursor(LoadCursor(nullptr, IDC_HAND));
                    return TRUE;
                }
            }
            break;
        }
        case WM_TIMER:
            if (wParam == kMetricsTimer) {
                refreshMetrics();
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            if (wParam == kPreviewTimer) {
                gTaskProgress += 2;
                if (gTaskProgress >= 100) {
                    gTaskProgress = 100;
                    KillTimer(hwnd, kPreviewTimer);
                    if (gTaskMode == TaskMode::Scan) gStatus = L"Preview scan complete · no file paths accessed";
                    else if (gTaskMode == TaskMode::NetworkTest) gStatus = L"Sample test complete · no network packets were sent";
                    else gStatus = L"Repair simulation complete · no command was executed";
                }
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            break;
        case WM_KEYDOWN:
            if (wParam == VK_F5 && gPage == Overview) {
                startPreviewTask(hwnd, TaskMode::Scan, L"Sample category review");
                return 0;
            }
            break;
        case WM_DESTROY:
            KillTimer(hwnd, kMetricsTimer);
            KillTimer(hwnd, kPreviewTimer);
            destroyFonts();
            PostQuitMessage(0);
            return 0;
        default:
            break;
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}

} // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand) {
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    WNDCLASSEXW windowClass{};
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = windowProc;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.lpszClassName = kWindowClass;
    if (!RegisterClassExW(&windowClass)) return 1;

    HWND hwnd = CreateWindowExW(0, kWindowClass, kWindowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1420, 900, nullptr, nullptr, instance, nullptr);
    if (!hwnd) return 2;
    gMainWindow = hwnd;

    ShowWindow(hwnd, showCommand);
    UpdateWindow(hwnd);

    MSG message{};
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }
    return static_cast<int>(message.wParam);
}
