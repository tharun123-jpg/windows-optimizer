const iconPaths = {
  grid: '<rect x="3.5" y="3.5" width="7" height="7" rx="1.4"/><rect x="13.5" y="3.5" width="7" height="7" rx="1.4"/><rect x="3.5" y="13.5" width="7" height="7" rx="1.4"/><rect x="13.5" y="13.5" width="7" height="7" rx="1.4"/>',
  broom: '<path d="m14.5 5.5 4 4M11 9l4-4 5 5-4 4M3.5 20.5c3.4-.4 5.4-2.2 6.3-5.8l2.1-1.5 3.9 3.9-1.6 2.1c-3.6.9-5.4 2.9-5.8 6.3" transform="translate(0 -2)"/><path d="m10.5 13.5 3.7 3.7"/>',
  gamepad: '<path d="M7 8h10a4 4 0 0 1 3.9 3.2l1 4.5a2.4 2.4 0 0 1-3.8 2.4l-2.5-1.9H8.4l-2.5 1.9a2.4 2.4 0 0 1-3.8-2.4l1-4.5A4 4 0 0 1 7 8Z"/><path d="M7.5 11v4M5.5 13h4M16.5 12h.01M18.5 14h.01"/>',
  cube: '<path d="m12 3 8 4.5v9L12 21l-8-4.5v-9L12 3Z"/><path d="m4.3 7.7 7.7 4.4 7.7-4.4M12 12.1V21M8 5.3l8 4.5"/>',
  network: '<circle cx="12" cy="5" r="2.2"/><circle cx="5" cy="18" r="2.2"/><circle cx="19" cy="18" r="2.2"/><path d="m10.8 6.8-4.5 9M13.2 6.8l4.5 9M7.2 18h9.6"/>',
  cpu: '<rect x="6" y="6" width="12" height="12" rx="2"/><path d="M9 9h6v6H9zM9 2.5v3.2M15 2.5v3.2M9 18.3v3.2M15 18.3v3.2M2.5 9h3.2M2.5 15h3.2M18.3 9h3.2M18.3 15h3.2"/>',
  gpu: '<rect x="3" y="5" width="18" height="14" rx="2"/><circle cx="10" cy="12" r="3.1"/><path d="M17 9h1M17 12h1M17 15h1M6 19v2M18 19v2"/>',
  rocket: '<path d="M12 15.5c3.2-2.2 5.7-5.8 6.1-11.6-5.8.4-9.4 2.9-11.6 6.1l5.5 5.5Z"/><path d="m6.5 10-3.2.7-.8 4.2 4.5-.8M14 17.5l-.7 3.2-4.2.8.8-4.5M8.3 16.7c-1.6.7-2.4 2-2.6 3.6 1.6-.2 2.9-1 3.6-2.6M14.5 8.5h.01"/><circle cx="14.5" cy="8.5" r="1.2"/>',
  layers: '<path d="m12 3 9 5-9 5-9-5 9-5Z"/><path d="m3 12 9 5 9-5M3 16l9 5 9-5"/>',
  wrench: '<path d="M14.6 6.1a5.4 5.4 0 0 0-6.7 6.7L3.7 17a2.2 2.2 0 0 0 3.1 3.1l4.2-4.2a5.4 5.4 0 0 0 6.7-6.7l-3 3-3.1-.8-.8-3.1 3.8-2.2Z"/><path d="m16.5 4.2 3.3 3.3"/>',
  rotate: '<path d="M20 7v5h-5M4 17v-5h5"/><path d="M6 9a7 7 0 0 1 11.8-2L20 9M4 15l2.2 2A7 7 0 0 0 18 15"/>',
  settings: '<circle cx="12" cy="12" r="3"/><path d="m19.4 15 .1.1 1.2 1-1.5 2.6-1.5-.6a8 8 0 0 1-1.7 1l-.3 1.6h-3l-.3-1.6a8 8 0 0 1-1.7-1l-1.5.6-1.5-2.6 1.2-1a8 8 0 0 1 0-2l-1.2-1 1.5-2.6 1.5.6a8 8 0 0 1 1.7-1l.3-1.6h3l.3 1.6a8 8 0 0 1 1.7 1l1.5-.6 1.5 2.6-1.2 1a8 8 0 0 1 0 2Z" transform="translate(-1 -1) scale(.95)"/>',
  chevron: '<path d="m9 18 6-6-6-6"/>',
  chevronDown: '<path d="m7 10 5 5 5-5"/>',
  arrowUpRight: '<path d="M7 17 17 7M8 7h9v9"/>',
  scan: '<path d="M4 8V5a1 1 0 0 1 1-1h3M16 4h3a1 1 0 0 1 1 1v3M20 16v3a1 1 0 0 1-1 1h-3M8 20H5a1 1 0 0 1-1-1v-3M4 12h16"/>',
  shield: '<path d="M12 3 19 6v5.4c0 4.3-2.8 7.3-7 9.1-4.2-1.8-7-4.8-7-9.1V6l7-3Z"/><path d="m9 12 2 2 4-4"/>',
  shieldCheck: '<path d="M12 3 19 6v5.4c0 4.3-2.8 7.3-7 9.1-4.2-1.8-7-4.8-7-9.1V6l7-3Z"/><path d="m9 12 2 2 4-4"/>',
  clock: '<circle cx="12" cy="12" r="8.5"/><path d="M12 7v5l3 2"/>',
  check: '<path d="m5 12 4 4L19 6"/>',
  plus: '<path d="M12 5v14M5 12h14"/>',
  search: '<circle cx="10.8" cy="10.8" r="6.8"/><path d="m16 16 4.5 4.5"/>',
  play: '<path d="m8 5 11 7-11 7V5Z"/>',
  download: '<path d="M12 3v12M7 10l5 5 5-5M4 20h16"/>',
  refresh: '<path d="M20 11a8 8 0 0 0-14.9-3M4 4v4h4M4 13a8 8 0 0 0 14.9 3M20 20v-4h-4"/>',
  info: '<circle cx="12" cy="12" r="9"/><path d="M12 11v5M12 8h.01"/>',
  close: '<path d="m6 6 12 12M18 6 6 18"/>',
  monitor: '<rect x="3" y="4" width="18" height="13" rx="2"/><path d="M8 21h8M12 17v4"/>',
  harddrive: '<rect x="3" y="5" width="18" height="14" rx="2"/><path d="M7 15h.01M11 15h.01M15 9h2M6 9h5"/>',
  memory: '<rect x="3" y="7" width="18" height="10" rx="2"/><path d="M7 4v3M11 4v3M15 4v3M19 4v3M7 17v3M11 17v3M15 17v3M19 17v3"/>',
  activity: '<path d="M3 12h4l3-8 4 16 3-8h4"/>',
  zap: '<path d="m13 2-3 9h7l-6 11 2-9H6l7-11Z"/>',
  wifi: '<path d="M5 9a11 11 0 0 1 14 0M8 12a6.5 6.5 0 0 1 8 0M10.5 15a2.5 2.5 0 0 1 3 0M12 19h.01"/>',
  terminal: '<path d="m5 7 5 5-5 5M12 17h7"/>',
  globe: '<circle cx="12" cy="12" r="9"/><path d="M3.5 12h17M12 3a14 14 0 0 1 0 18M12 3a14 14 0 0 0 0 18"/>',
  save: '<path d="M5 3h12l4 4v13a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1V4a1 1 0 0 1 1-1Z"/><path d="M7 3v6h10V3M7 21v-8h10v8"/>',
  trash: '<path d="M4 7h16M10 11v6M14 11v6M5.5 7l1 13h11l1-13M9 7V4h6v3"/>',
  eye: '<path d="M2.5 12s3.3-6 9.5-6 9.5 6 9.5 6-3.3 6-9.5 6-9.5-6-9.5-6Z"/><circle cx="12" cy="12" r="2.5"/>',
  battery: '<rect x="3" y="7" width="17" height="10" rx="2"/><path d="M22 10v4M7 10v4M11 10v4M15 10v4"/>',
  power: '<path d="M12 3v9M6.2 6.5a8 8 0 1 0 11.6 0"/>',
  list: '<path d="M9 6h11M9 12h11M9 18h11M4 6h.01M4 12h.01M4 18h.01"/>',
  box: '<path d="m12 3 9 5-9 5-9-5 9-5Z"/><path d="M3 8v8l9 5 9-5V8M12 13v8"/>',
  target: '<circle cx="12" cy="12" r="9"/><circle cx="12" cy="12" r="5"/><circle cx="12" cy="12" r="1"/>',
  server: '<rect x="4" y="3" width="16" height="8" rx="2"/><rect x="4" y="13" width="16" height="8" rx="2"/><path d="M8 7h.01M8 17h.01M12 7h4M12 17h4"/>',
  cpu2: '<path d="M8 8h8v8H8z"/><path d="M9 2.5v3M15 2.5v3M9 18.5v3M15 18.5v3M2.5 9h3M2.5 15h3M18.5 9h3M18.5 15h3"/>',
  sparkle: '<path d="m12 3 1.7 5.3L19 10l-5.3 1.7L12 17l-1.7-5.3L5 10l5.3-1.7L12 3ZM19 16l.8 2.2L22 19l-2.2.8L19 22l-.8-2.2L16 19l2.2-.8L19 16Z"/>',
  sliders: '<path d="M4 21v-7M4 10V3M12 21v-9M12 8V3M20 21v-5M20 12V3M2 14h4M10 8h4M18 16h4"/>',
  history: '<path d="M3 12a9 9 0 1 0 2.6-6.4L3 8M3 3v5h5"/><path d="M12 7v5l3 2"/>',
  lock: '<rect x="4" y="10" width="16" height="11" rx="2"/><path d="M8 10V7a4 4 0 0 1 8 0v3M12 14v3"/>',
  globe2: '<circle cx="12" cy="12" r="9"/><path d="M3 12h18M12 3a15 15 0 0 1 0 18M12 3a15 15 0 0 0 0 18"/>',
  key: '<circle cx="8" cy="15" r="4"/><path d="m11 12 9-9M16 7l2 2M18 5l2 2"/>',
  book: '<path d="M4 4.5A2.5 2.5 0 0 1 6.5 2H20v18H6.5A2.5 2.5 0 0 0 4 22V4.5Z"/><path d="M4 18a2.5 2.5 0 0 1 2.5-2.5H20"/>',
  alert: '<path d="m12 3 9 16H3l9-16Z"/><path d="M12 9v4M12 16h.01"/>',
  mouse: '<rect x="6" y="3" width="12" height="18" rx="6"/><path d="M12 3v6"/>',
  code: '<path d="m8 8-4 4 4 4M16 8l4 4-4 4M14 5l-4 14"/>',
};

function icon(name, extraClass = '') {
  const shape = iconPaths[name] || iconPaths.info;
  return `<svg class="${extraClass}" viewBox="0 0 24 24" fill="none" aria-hidden="true">${shape}</svg>`;
}

const navigation = [
  { group: 'Workspace', items: [
    { key: 'overview', label: 'Overview', icon: 'grid' },
    { key: 'cleaner', label: 'Windows Cleaner', icon: 'broom', count: '14.8 GB' },
    { key: 'gaming', label: 'Gaming', icon: 'gamepad' },
    { key: 'minecraft', label: 'Minecraft', icon: 'cube', badge: 'FOCUS' },
  ] },
  { group: 'Performance', items: [
    { key: 'network', label: 'Network', icon: 'network' },
    { key: 'hardware', label: 'Hardware & BIOS', icon: 'cpu' },
  ] },
  { group: 'Windows', items: [
    { key: 'startup', label: 'Startup Manager', icon: 'rocket', count: '6' },
    { key: 'services', label: 'Services', icon: 'layers' },
    { key: 'privacy', label: 'Privacy', icon: 'lock' },
    { key: 'debloat', label: 'Debloat', icon: 'box' },
    { key: 'repair', label: 'System Repair', icon: 'wrench' },
  ] },
  { group: 'Safety', items: [
    { key: 'restore', label: 'Restore Center', icon: 'history' },
    { key: 'settings', label: 'Settings', icon: 'settings' },
  ] },
];

const profiles = [
  { id: 'Safe', label: 'Safe', icon: 'shield', color: 'lime', desc: 'Conservative, reversible tune-up.' },
  { id: 'Gaming', label: 'Gaming', icon: 'gamepad', color: 'blue', desc: 'Prioritize a smoother play session.' },
  { id: 'Minecraft PvP', label: 'Minecraft PvP', icon: 'target', color: 'purple', desc: 'Lean setup for competitive play.' },
  { id: 'Maximum Performance', label: 'Maximum performance', icon: 'zap', color: 'orange', desc: 'More aggressive, always review first.' },
  { id: 'Editing', label: 'Editing', icon: 'layers', color: 'blue', desc: 'Keep creator tools responsive.' },
  { id: 'Custom', label: 'Custom', icon: 'sliders', color: 'purple', desc: 'Choose each setting yourself.' },
];

const profileChecklists = {
  Safe: ['Review temporary files', 'Keep Windows defaults', 'Check startup impact', 'Restore-first workflow'],
  Gaming: ['Game Mode', 'Power profile review', 'Capture controls', 'Background app review'],
  'Minecraft PvP': ['Java version check', 'RAM allocation check', 'Game Mode', 'Minecraft priority review'],
  'Maximum Performance': ['Power plan review', 'Game Mode', 'Startup review', 'Restore point prompt'],
  Editing: ['Creator app priority', 'Background capture review', 'Balanced power plan', 'Memory headroom check'],
  Custom: ['Choose individual settings', 'No automatic toggles', 'Preview changes', 'Restore-first workflow'],
};

const cleanerItems = [
  { id: 'temp', name: 'Temporary files', place: 'User & Windows temp folders', mb: 2458, safe: true, icon: 'broom' },
  { id: 'shader', name: 'DirectX Shader Cache', place: 'GPU shader cache', mb: 846, safe: true, icon: 'gpu' },
  { id: 'delivery', name: 'Delivery Optimization', place: 'Update delivery cache', mb: 611, safe: true, icon: 'download' },
  { id: 'thumbs', name: 'Thumbnail cache', place: 'Explorer image previews', mb: 210, safe: true, icon: 'eye' },
  { id: 'update', name: 'Windows Update cache', place: 'Downloaded update files', mb: 1331, safe: false, icon: 'refresh' },
  { id: 'prefetch', name: 'Prefetch data', place: 'Windows app-start traces', mb: 128, safe: false, icon: 'activity' },
  { id: 'recycle', name: 'Recycle Bin', place: 'Items awaiting permanent deletion', mb: 8050, safe: false, icon: 'trash' },
  { id: 'browser', name: 'Browser cache', place: 'Temporary web files · sample', mb: 1106, safe: true, icon: 'globe' },
  { id: 'dns', name: 'DNS cache', place: 'Resolver cache · no disk space', mb: 0, safe: false, icon: 'network' },
  { id: 'dumps', name: 'Crash dumps', place: 'System error dump files', mb: 334, safe: true, icon: 'alert' },
  { id: 'reports', name: 'Error reports', place: 'Windows error reporting files', mb: 76, safe: true, icon: 'list' },
  { id: 'old-logs', name: 'Old Windows logs', place: 'Archived setup and event logs', mb: 18, safe: true, icon: 'list' },
  { id: 'app-cache', name: 'App cache', place: 'Optional app caches · sample', mb: 12, safe: false, icon: 'layers' },
  { id: 'defender-cache', name: 'Defender history cache', place: 'Protection history · review only', mb: 8, safe: false, icon: 'shield' },
];

const startupDefaults = [
  { id: 'discord', name: 'Discord', publisher: 'Discord Inc.', impact: 'Medium', source: 'User Run key', monogram: 'D', enabled: true },
  { id: 'steam', name: 'Steam', publisher: 'Valve Corporation', impact: 'High', source: 'Startup folder', monogram: 'S', enabled: true },
  { id: 'onedrive', name: 'OneDrive', publisher: 'Microsoft', impact: 'Medium', source: 'User Run key', monogram: 'O', enabled: true },
  { id: 'epic', name: 'Epic Games Launcher', publisher: 'Epic Games', impact: 'High', source: 'User Run key', monogram: 'E', enabled: true },
  { id: 'teams', name: 'Microsoft Teams', publisher: 'Microsoft', impact: 'High', source: 'Startup task', monogram: 'T', enabled: true },
  { id: 'spotify', name: 'Spotify', publisher: 'Spotify AB', impact: 'Low', source: 'User Run key', monogram: 'S', enabled: false },
  { id: 'minecraft-launcher', name: 'Minecraft Launcher', publisher: 'Microsoft Studios', impact: 'Low', source: 'Startup folder', monogram: 'M', enabled: false },
  { id: 'adobe', name: 'Adobe Updater', publisher: 'Adobe Inc.', impact: 'Medium', source: 'Scheduled task', monogram: 'A', enabled: true },
];

const serviceDefaults = [
  { id: 'sysmain', name: 'SysMain', service: 'SysMain', state: 'Running', startup: 'Automatic', publisher: 'Microsoft', recommendation: 'Keep default', note: 'Windows manages preloading based on your usage. Disabling it can make app starts slower on some PCs.' },
  { id: 'wsearch', name: 'Windows Search', service: 'WSearch', state: 'Running', startup: 'Automatic (delayed)', publisher: 'Microsoft', recommendation: 'Keep default', note: 'Keep this enabled if you rely on Start-menu or File Explorer indexing.' },
  { id: 'spooler', name: 'Print Spooler', service: 'Spooler', state: 'Running', startup: 'Automatic', publisher: 'Microsoft', recommendation: 'Conditional', note: 'Only consider changing this when the PC never prints and no app requires printing.' },
  { id: 'xbox-auth', name: 'Xbox Live Auth Manager', service: 'XblAuthManager', state: 'Stopped', startup: 'Manual', publisher: 'Microsoft', recommendation: 'Keep default', note: 'Xbox sign-in, Game Pass, and Microsoft Store games may depend on this service.' },
  { id: 'gaming', name: 'Gaming Services', service: 'GamingServices', state: 'Running', startup: 'Automatic', publisher: 'Microsoft', recommendation: 'Keep default', note: 'Required by some Xbox and Microsoft Store games. Do not disable blindly.' },
  { id: 'diag', name: 'Diagnostic Policy Service', service: 'DPS', state: 'Running', startup: 'Automatic', publisher: 'Microsoft', recommendation: 'Keep default', note: 'Windows troubleshooting uses this service; there is no safe universal performance gain from disabling it.' },
  { id: 'adobe-update', name: 'Adobe Update Service', service: 'AdobeUpdateService', state: 'Running', startup: 'Automatic', publisher: 'Third-party', recommendation: 'Review vendor', note: 'Review the publisher and update policy before changing third-party services.' },
];

const privacyDefaults = {
  advertisingId: true,
  diagnostics: true,
  activityHistory: true,
  backgroundApps: true,
};

const debloatItems = [
  { id: 'clipchamp', name: 'Clipchamp', publisher: 'Microsoft', category: 'Video editor', note: 'Remove only if you do not use the built-in editor.' },
  { id: 'news', name: 'Microsoft News', publisher: 'Microsoft', category: 'News & interests', note: 'Optional app; can be reinstalled from Microsoft Store.' },
  { id: 'weather', name: 'Weather', publisher: 'Microsoft', category: 'Widgets', note: 'Optional app; check widget use before removal.' },
  { id: 'teams-personal', name: 'Teams (personal)', publisher: 'Microsoft', category: 'Messaging', note: 'Keep if you use personal or family calls.' },
  { id: 'xbox', name: 'Xbox app', publisher: 'Microsoft', category: 'Gaming', note: 'Keep for Game Pass, Xbox services, captures, or Store games.' },
  { id: 'mixed-reality', name: 'Mixed Reality Portal', publisher: 'Microsoft', category: 'Optional feature', note: 'Only relevant if you do not use a supported VR headset.' },
];

const repairOptions = [
  { id: 'sfc', name: 'System File Checker', short: 'SFC', icon: 'shieldCheck', duration: '10–20 min', desc: 'Checks protected Windows files and can repair common corruption.' },
  { id: 'dism', name: 'DISM image repair', short: 'DISM', icon: 'wrench', duration: '10–30 min', desc: 'Checks the component image. Typically run before SFC if corruption is found.' },
  { id: 'chkdsk', name: 'Disk check', short: 'CHKDSK', icon: 'harddrive', duration: 'Varies', desc: 'Reviews file-system health. Some repairs may require a reboot.' },
  { id: 'update-repair', name: 'Windows Update repair', short: 'UPDATE', icon: 'refresh', duration: '5–15 min', desc: 'Guided checks for common Windows Update issues.' },
  { id: 'network-repair', name: 'Network repair', short: 'NETWORK', icon: 'network', duration: '2–5 min', desc: 'Review diagnostics before considering a reset. May disconnect networking.' },
  { id: 'component-store', name: 'Component Store check', short: 'STORE', icon: 'box', duration: '5–15 min', desc: 'Checks the Windows component store without removing user files.' },
];

const initialSnapshots = [
  { id: 'session-start', title: 'Preview session started', time: 'This session', type: 'Browser-only snapshot', profile: 'Safe' },
];

const state = {
  page: 'overview',
  profile: 'Safe',
  hardwareTab: 'CPU',
  serviceFilter: 'All services',
  dnsProfile: 'Cloudflare',
  networkResult: null,
  networkRunning: false,
  networkProgress: 0,
  scanRunning: false,
  scanProgress: 0,
  cleanerScanned: false,
  cleanerSelection: Object.fromEntries(cleanerItems.map((item) => [item.id, item.safe])),
  gaming: { gameMode: true, hags: false, fullscreen: true, backgroundCapture: false, xboxGameBar: true },
  startup: startupDefaults.map((item) => ({ ...item })),
  services: serviceDefaults.map((item) => ({ ...item })),
  privacy: { ...privacyDefaults },
  settings: { notifications: true, startup: false, compactMode: false },
  startupSearch: '',
  minecraftRam: 6,
  minecraftProfile: 'PvP',
  jvmPreset: 'Balanced',
  snapshots: [...initialSnapshots],
  lastRun: null,
  activity: [
    { title: 'Sample device profile loaded', detail: 'i5-7500 · GTX 1050 Ti · 16 GB RAM', time: 'This session', icon: 'monitor' },
    { title: 'No Windows changes applied', detail: 'The interface is running in browser preview mode.', time: 'Just now', icon: 'shield' },
  ],
  repair: { running: false, progress: 0, name: '', log: ['THARU SYSTEM REPAIR · PREVIEW CONSOLE', 'No system commands have been executed.', 'Choose a diagnostic to see a simulated progress flow.'] },
  modalConfirm: null,
};

const $ = (selector, root = document) => root.querySelector(selector);
const $$ = (selector, root = document) => [...root.querySelectorAll(selector)];
const pageContent = $('#pageContent');
const modalRoot = $('#modalRoot');
const toastRoot = $('#toastRoot');

function escapeHTML(value) {
  return String(value).replace(/[&<>"']/g, (char) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' })[char]);
}

function formatSize(mb) {
  if (mb <= 0) return '0 B';
  if (mb < 1) return `${Math.max(1, Math.round(mb * 1024))} KB`;
  if (mb >= 1024) return `${(mb / 1024).toFixed(mb >= 10 * 1024 ? 0 : 1)} GB`;
  return `${Math.round(mb)} MB`;
}

function formatDate() {
  return new Intl.DateTimeFormat('en-US', { weekday: 'long', month: 'long', day: 'numeric', year: 'numeric' }).format(new Date()).toUpperCase();
}

function getSelectedCleanerSize() {
  return cleanerItems.reduce((sum, item) => sum + (state.cleanerSelection[item.id] ? item.mb : 0), 0);
}

function getPotentialCleanerSize() {
  return cleanerItems.reduce((sum, item) => sum + item.mb, 0);
}

function renderNavigation() {
  const nav = $('#sidebarNav');
  nav.innerHTML = navigation.map((section) => `
    <div class="nav-group">
      <p class="nav-label">${section.group}</p>
      ${section.items.map((item) => `
        <button class="nav-link ${state.page === item.key ? 'active' : ''}" type="button" data-nav="${item.key}" ${state.page === item.key ? 'aria-current="page"' : ''}>
          <span class="nav-icon">${icon(item.icon)}</span>
          <span class="nav-text">${item.label}</span>
          ${item.badge ? `<span class="nav-badge">${item.badge}</span>` : item.key === 'cleaner' ? `<span class="nav-count">${formatSize(getPotentialCleanerSize())}</span>` : item.count ? `<span class="nav-count">${item.count}</span>` : ''}
        </button>`).join('')}
    </div>`).join('');
}

function updatePageChrome() {
  const activeItem = navigation.flatMap((group) => group.items).find((item) => item.key === state.page);
  $('#breadcrumbCurrent').textContent = activeItem?.label || 'Overview';
  document.title = `${activeItem?.label || 'Overview'} · THARU OPTIMIZER`;
  renderNavigation();
}

function pageHeader(title, description, eyebrow = 'SYSTEM CENTER', actions = '') {
  return `
    <div class="page-heading">
      <div>
        <p class="eyebrow"><span class="eyebrow-dot"></span>${eyebrow}</p>
        <h1>${title}</h1>
        <p>${description}</p>
      </div>
      ${actions ? `<div class="heading-actions">${actions}</div>` : ''}
    </div>`;
}

function progressMarkup(kind, progress, label, visible = true) {
  return `<div class="scan-progress ${visible ? 'visible' : ''}">
    <div class="scan-progress-meta"><span data-progress-label="${kind}">${escapeHTML(label)}</span><span data-progress-value="${kind}">${Math.round(progress)}%</span></div>
    <div class="meter"><span data-progress="${kind}" style="width:${Math.round(progress)}%"></span></div>
  </div>`;
}

function renderOverview() {
  const selectedSize = formatSize(getSelectedCleanerSize());
  const lastRunText = state.lastRun ? new Intl.DateTimeFormat('en-US', { month: 'short', day: 'numeric', hour: 'numeric', minute: '2-digit' }).format(new Date(state.lastRun)) : 'Not run yet';
  const activity = state.activity[0];
  return `
    <div class="page-heading dashboard-head">
      <div class="page-heading-left">
        <p class="eyebrow"><span class="eyebrow-dot"></span>${formatDate()}</p>
        <h1>Your PC, in balance.</h1>
        <div class="dashboard-topline"><span class="sample-tag">SAMPLE DEVICE DATA</span><span class="status-text"><i></i>Ready for review</span></div>
      </div>
      <div class="heading-actions">
        <button class="button button-quiet" type="button" data-action="create-restore">${icon('history')} Restore point</button>
      </div>
    </div>

    <section class="dashboard-grid" aria-label="System overview">
      <article class="card health-card">
        <div class="health-card-head">
          <div class="label-caps">System health · sample score</div>
          <span class="pill pill-green">Good shape</span>
        </div>
        <div class="health-card-body">
          <div class="health-ring" role="img" aria-label="Sample system health score 86 out of 100">
            <div class="health-ring-inner"><strong>86</strong><span>OUT OF 100</span></div>
          </div>
          <div class="health-copy">
            <h2>Looking good.</h2>
            <p>A quick review found a few optional cleanups and settings to check. Nothing is changed without your say-so.</p>
            <button class="button button-secondary button-small" type="button" data-action="scan-system">${icon('scan')} ${state.scanRunning ? 'Scanning…' : 'Run quick scan'}</button>
          </div>
        </div>
        <div class="health-highlights">
          <span class="health-highlight">${icon('check')} No critical alerts</span>
          <span class="health-highlight">${icon('shield')} Restore-first flow</span>
          <span class="health-highlight">${icon('info')} Sample values only</span>
        </div>
        ${state.scanRunning ? progressMarkup('scan', state.scanProgress, 'Preview scan in progress…') : ''}
      </article>

      <article class="card performance-card">
        <div class="performance-title"><div><h2>Performance snapshot</h2><p>Sample telemetry · not connected to Windows</p></div><span class="pill pill-blue">SAMPLE</span></div>
        <div class="performance-score">
          <div class="performance-row"><span class="metric-name">Windows</span><div class="meter"><span style="width:92%"></span></div><strong>92%</strong></div>
          <div class="performance-row"><span class="metric-name">Gaming</span><div class="meter blue"><span style="width:87%"></span></div><strong>87%</strong></div>
          <div class="performance-row"><span class="metric-name">Network</span><div class="meter purple"><span style="width:81%"></span></div><strong>81%</strong></div>
        </div>
        <div class="performance-footer"><span>Last optimization</span><strong>${escapeHTML(lastRunText)}</strong></div>
      </article>
    </section>

    <section class="metric-grid" aria-label="Sample hardware metrics">
      <article class="card metric-card">
        <div class="metric-card-top"><span class="metric-caption">Processor</span><span class="metric-icon blue">${icon('cpu')}</span></div>
        <div class="metric-value">34<small>%</small></div>
        <div class="metric-detail"><span>Intel Core i5-7500</span><strong>3.40 GHz</strong></div><div class="meter blue"><span style="width:34%"></span></div>
      </article>
      <article class="card metric-card">
        <div class="metric-card-top"><span class="metric-caption">Memory</span><span class="metric-icon purple">${icon('memory')}</span></div>
        <div class="metric-value">9.8<small>/ 16 GB</small></div>
        <div class="metric-detail"><span>In use</span><strong>61%</strong></div><div class="meter purple"><span style="width:61%"></span></div>
      </article>
      <article class="card metric-card">
        <div class="metric-card-top"><span class="metric-caption">Graphics</span><span class="metric-icon orange">${icon('gpu')}</span></div>
        <div class="metric-value">42<small>%</small></div>
        <div class="metric-detail"><span>GeForce GTX 1050 Ti</span><strong>Sample</strong></div><div class="meter orange"><span style="width:42%"></span></div>
      </article>
      <article class="card metric-card">
        <div class="metric-card-top"><span class="metric-caption">System drive</span><span class="metric-icon lime">${icon('harddrive')}</span></div>
        <div class="metric-value">71<small>%</small></div>
        <div class="metric-detail"><span>337 GB free</span><strong>1.2 TB</strong></div><div class="meter"><span style="width:71%"></span></div>
      </article>
    </section>

    <section class="overview-detail-grid" aria-label="Additional sample system status">
      <div class="overview-detail"><span class="overview-detail-icon blue">${icon('wifi')}</span><span><small>Network latency</small><strong>24 ms <em>sample</em></strong></span></div>
      <div class="overview-detail"><span class="overview-detail-icon purple">${icon('rocket')}</span><span><small>Startup apps</small><strong>6 enabled <em>of 8</em></strong></span></div>
      <div class="overview-detail"><span class="overview-detail-icon lime">${icon('broom')}</span><span><small>Temp & cache found</small><strong>${formatSize(getPotentialCleanerSize())} <em>sample</em></strong></span></div>
      <div class="overview-detail"><span class="overview-detail-icon orange">${icon('clock')}</span><span><small>Last optimization</small><strong>${escapeHTML(lastRunText)}</strong></span></div>
    </section>

    <section class="lower-grid">
      <article class="card optimize-card">
        <div class="optimize-head"><div><p class="label-caps">Your next steps</p><h2 style="margin-top:6px">Ready when you are.</h2><p>Review a safe profile before making any system changes.</p></div><span class="pill pill-green">${escapeHTML(state.profile)}</span></div>
        <div class="optimize-list">
          <div class="optimize-row"><span class="check-dot">${icon('check')}</span><span>Files to review</span><strong>${escapeHTML(selectedSize)}</strong></div>
          <div class="optimize-row"><span class="check-dot">${icon('check')}</span><span>Startup suggestions</span><strong>3 apps</strong></div>
          <div class="optimize-row"><span class="check-dot">${icon('check')}</span><span>Gaming settings</span><strong>3 checks</strong></div>
          <div class="optimize-row"><span class="check-dot">${icon('check')}</span><span>Minecraft RAM guide</span><strong>6 GB</strong></div>
        </div>
        <div class="optimize-footer"><span class="helper">Restore-first · no changes without confirmation</span><button class="button button-primary" type="button" data-action="optimize-now">${icon('zap')} OPTIMIZE NOW</button></div>
      </article>
      <div class="side-stack">
        <article class="card profile-mini">
          <div class="profile-mini-head"><div><h3>Optimization profile</h3><p>Choose a starting point</p></div><span class="metric-icon lime">${icon('sliders')}</span></div>
          <div class="profile-select-wrap"><select class="select-control" id="dashboardProfile" aria-label="Choose an optimization profile">${profiles.map((profile) => `<option value="${escapeHTML(profile.id)}" ${state.profile === profile.id ? 'selected' : ''}>${escapeHTML(profile.label)}</option>`).join('')}</select><span class="select-chevron">${icon('chevronDown')}</span></div>
          <div class="profile-select-foot"><span>${escapeHTML(profiles.find((p) => p.id === state.profile)?.desc || '')}</span><button class="subtle-link" type="button" data-nav="gaming">Customize →</button></div>
        </article>
        <article class="card last-run-card">
          <span class="last-run-icon">${icon(activity?.icon || 'history')}</span>
          <span class="last-run-copy"><strong>${escapeHTML(activity?.title || 'No activity yet')}</strong><span>${escapeHTML(activity?.detail || 'Your preview history will appear here.')}</span></span>
          <button class="subtle-link last-run-link" type="button" data-nav="restore" aria-label="Open restore center">›</button>
        </article>
      </div>
    </section>

    <section class="quick-access" aria-label="Quick access">
      <button class="quick-tile" type="button" data-nav="cleaner"><span class="metric-icon lime">${icon('broom')}</span><span class="quick-tile-copy"><strong>Windows Cleaner</strong><small>${formatSize(getPotentialCleanerSize())} sample estimate</small></span><span class="quick-tile-arrow">›</span></button>
      <button class="quick-tile" type="button" data-nav="gaming"><span class="metric-icon blue">${icon('gamepad')}</span><span class="quick-tile-copy"><strong>Gaming setup</strong><small>Review 3 available settings</small></span><span class="quick-tile-arrow">›</span></button>
      <button class="quick-tile" type="button" data-nav="minecraft"><span class="metric-icon purple">${icon('cube')}</span><span class="quick-tile-copy"><strong>Minecraft profile</strong><small>Java, RAM & launcher guide</small></span><span class="quick-tile-arrow">›</span></button>
      <button class="quick-tile" type="button" data-nav="restore"><span class="metric-icon orange">${icon('history')}</span><span class="quick-tile-copy"><strong>Restore Center</strong><small>Preview backup & undo flow</small></span><span class="quick-tile-arrow">›</span></button>
    </section>

    <div class="preview-callout" style="margin-top:16px">${icon('info')}<span><strong>Browser preview:</strong> all hardware values are sample data. This UI cannot inspect your PC or change Windows, services, files, registry, network, or startup settings.</span></div>`;
}

function renderCleaner() {
  const selectedMb = getSelectedCleanerSize();
  return `${pageHeader('Windows Cleaner', 'Review temporary and cache categories individually. Nothing is deleted by this browser preview.', 'CLEANUP TOOLS', `<button class="button button-secondary" type="button" data-action="select-safe">${icon('check')} Select safe items</button>`)}
    <section class="cleaner-summary">
      <div><h2>Review before reclaiming space</h2><p>Sample scan result across ${cleanerItems.length} categories. Sensitive locations stay unchecked until you choose them.</p></div>
      <div class="cleaner-estimate"><div class="cleaner-estimate-copy"><span>Potential found · sample</span><strong>${formatSize(getPotentialCleanerSize())}</strong></div><button class="button button-primary" type="button" data-action="scan-system">${icon('scan')} ${state.scanRunning ? 'Scanning…' : 'Scan again'}</button></div>
    </section>
    ${state.scanRunning ? progressMarkup('scan', state.scanProgress, 'Preview scan in progress…') : state.cleanerScanned ? `<div class="inline-note" style="margin:12px 0 0">${icon('check')}Latest preview scan complete. This is a static sample estimate, not a scan of your drive.</div>` : ''}
    <div class="cleaner-toolbar"><div class="toolbar-left"><span>${cleanerItems.length} categories</span><span>·</span><span>${formatSize(selectedMb)} selected</span></div><div class="toolbar-left"><button class="subtle-link" type="button" data-action="select-all">Select all</button><button class="subtle-link" type="button" data-action="clear-cleaner-selection">Clear</button></div></div>
    <div class="cleaner-grid">${cleanerItems.map((item) => `
      <article class="cleaner-item">
        <label class="cleaner-check" title="Select ${escapeHTML(item.name)}"><input type="checkbox" data-cleaner-toggle="${item.id}" ${state.cleanerSelection[item.id] ? 'checked' : ''} aria-label="Select ${escapeHTML(item.name)}">${icon('check')}</label>
        <span class="cleaner-item-icon">${icon(item.icon)}</span>
        <span class="cleaner-item-copy"><strong>${escapeHTML(item.name)}</strong><small>${escapeHTML(item.place)}</small></span>
        <span class="cleaner-item-trailing"><span class="cleaner-size">${formatSize(item.mb)}</span><span class="cleaner-risk ${item.safe ? '' : 'review'}">${item.safe ? 'Low risk' : 'Review'}</span></span>
      </article>`).join('')}</div>
    <section class="section-block card card-pad">
      <div class="section-title"><div><h2>Cleanup review</h2><p>For a native Windows app, each category should be re-measured and permission-checked immediately before deletion.</p></div><button class="button button-primary" type="button" data-action="review-cleanup" ${selectedMb <= 0 ? 'disabled' : ''}>Review ${formatSize(selectedMb)} ${icon('chevron')}</button></div>
      <div class="preview-callout">${icon('alert')}<span><strong>Not a real scan or cleanup.</strong> Browser preview does not read file paths, estimate live disk usage, empty the Recycle Bin, or remove caches.</span></div>
    </section>`;
}

function renderProfileCards() {
  return `<div class="profile-grid">${profiles.map((profile) => `
    <button class="profile-card ${state.profile === profile.id ? 'selected' : ''}" type="button" data-profile="${escapeHTML(profile.id)}" aria-pressed="${state.profile === profile.id}">
      <span class="profile-card-top"><span class="profile-card-icon ${profile.color}">${icon(profile.icon)}</span><span class="profile-selected-mark">${icon('check')}</span></span>
      <strong>${escapeHTML(profile.label)}</strong><small>${escapeHTML(profile.desc)}</small>
    </button>`).join('')}</div>`;
}

function switchInput(key, checked, label, attr = 'data-gaming-toggle') {
  return `<label class="switch" title="${escapeHTML(label)}"><input type="checkbox" ${attr}="${escapeHTML(key)}" ${checked ? 'checked' : ''} aria-label="${escapeHTML(label)}"><span></span></label>`;
}

function renderGaming() {
  const checklist = profileChecklists[state.profile] || profileChecklists.Safe;
  const gamingOptions = [
    { key: 'gameMode', title: 'Windows Game Mode', desc: 'A Windows setting that prioritizes a game while it is active.', value: state.gaming.gameMode, badge: 'Recommended' },
    { key: 'hags', title: 'Hardware-accelerated GPU scheduling', desc: 'Availability depends on GPU, driver, and Windows version. Verify support first.', value: state.gaming.hags, badge: 'Check support' },
    { key: 'fullscreen', title: 'Fullscreen optimizations', desc: 'Per-game behavior varies; compare frame pacing before changing it.', value: state.gaming.fullscreen, badge: 'Per game' },
    { key: 'backgroundCapture', title: 'Background capture', desc: 'Capturing clips can use CPU, GPU, storage, and memory while you play.', value: state.gaming.backgroundCapture, badge: 'Optional' },
    { key: 'xboxGameBar', title: 'Xbox Game Bar', desc: 'Keep enabled if you use its overlay, widgets, or controller shortcuts.', value: state.gaming.xboxGameBar, badge: 'Optional' },
  ];
  return `${pageHeader('Gaming Optimizer', 'Set up a reversible gaming profile. Every control here changes preview state only.', 'GAMING & PERFORMANCE', `<button class="button button-primary" type="button" data-action="apply-profile">${icon('zap')} Preview selected profile</button>`)}
    <section class="section-block" style="margin-top:0"><div class="section-title"><div><h2>Optimization profiles</h2><p>Choose a profile to review. No setting is applied automatically.</p></div><span class="pill pill-orange">Restore-first</span></div>${renderProfileCards()}</section>
    <section class="content-grid section-block">
      <article class="card card-pad"><div class="card-heading"><div><h2>${escapeHTML(state.profile)} checklist</h2><p>A quick map of what this profile would review.</p></div><span class="pill pill-green">Preview</span></div><div class="divider"></div><div class="profile-details">${checklist.map((item) => `<div class="profile-detail">${icon('check')}<span>${escapeHTML(item)}</span></div>`).join('')}</div><div class="divider"></div><div class="preview-callout">${icon('info')}<span>Profiles are recommendations, not performance guarantees. Restore points and measured before/after testing belong in the native Windows build.</span></div></article>
      <article class="card card-pad"><div class="card-heading"><div><h2>Windows gaming settings</h2><p>Sample switch states for an example PC.</p></div><span class="pill pill-blue">SAMPLE</span></div><div style="margin-top:8px">${gamingOptions.map((option) => `<div class="feature-row"><span class="feature-copy"><strong>${escapeHTML(option.title)}</strong><small>${escapeHTML(option.desc)}</small></span><span class="feature-trailing"><span class="switch-label">${escapeHTML(option.badge)}</span>${switchInput(option.key, option.value, option.title)}</span></div>`).join('')}</div></article>
    </section>
    <section class="section-block card card-pad"><div class="section-title"><div><h2>Session priorities</h2><p>Options to review before a game starts.</p></div></div><div class="content-grid equal"><div class="feature-row"><span class="icon-box lime">${icon('battery')}</span><span class="feature-copy"><strong>Power plan</strong><small>Sample plan: Balanced. Avoid forcing an aggressive plan on every device.</small></span><span class="pill pill-green">Balanced</span></div><div class="feature-row"><span class="icon-box blue">${icon('activity')}</span><span class="feature-copy"><strong>Process priority</strong><small>Normal is the safe default. High priority can make the desktop less responsive.</small></span><button class="button button-quiet button-small" type="button" data-action="priority-review">Review</button></div></div></section>`;
}

const launchers = [
  { name: 'Minecraft Launcher', initial: 'M', found: true, detail: 'Official launcher · sample' },
  { name: 'Prism Launcher', initial: 'P', found: true, detail: 'Multi-instance · sample' },
  { name: 'Feather', initial: 'F', found: true, detail: 'Client · sample' },
  { name: 'Lunar Client', initial: 'L', found: false, detail: 'Not in sample' },
  { name: 'Badlion Client', initial: 'B', found: false, detail: 'Not in sample' },
  { name: 'TLauncher', initial: 'T', found: false, detail: 'Not in sample' },
];

function renderMinecraft() {
  const maxRam = 10;
  const recommended = state.minecraftRam >= 4 && state.minecraftRam <= 8;
  const args = state.jvmPreset === 'Minimal' ? `-Xms2G -Xmx${state.minecraftRam}G -XX:+UseG1GC` : `-Xms2G -Xmx${state.minecraftRam}G -XX:+UseG1GC -XX:MaxGCPauseMillis=50 -XX:G1ReservePercent=20`;
  const minecraftProfiles = [
    { id: 'PvP', icon: 'target', color: 'purple', label: 'PvP', desc: 'Low overhead · no shader assumptions' },
    { id: 'Smooth FPS', icon: 'activity', color: 'blue', label: 'Smooth FPS', desc: 'Steady frame pacing baseline' },
    { id: 'Shaders', icon: 'sparkle', color: 'orange', label: 'Shaders', desc: 'Leave more memory for the GPU' },
    { id: 'Recording', icon: 'layers', color: 'lime', label: 'Recording', desc: 'Headroom for capture software' },
  ];
  return `${pageHeader('Minecraft Optimizer', 'Launcher detection, Java guidance, and sensible RAM presets — tailored to an older gaming PC.', 'MINECRAFT · PRIMARY FOCUS', `<button class="button button-secondary" type="button" data-action="minecraft-rescan">${icon('refresh')} Recheck launchers</button>`)}
    <section class="card minecraft-hero"><div class="minecraft-hero-main"><span class="minecraft-logo">${icon('cube')}</span><span class="minecraft-hero-copy"><h2>A smoother session starts with a sensible baseline.</h2><p>Sample profile for an i5-7500, GTX 1050 Ti, and 16 GB RAM. This page cannot detect launchers or Java in your browser.</p></span></div></section>
    <section class="content-grid section-block">
      <div class="content-stack">
        <article class="card card-pad"><div class="card-heading"><div><h2>Launcher availability</h2><p>Example results · not scanned from this device</p></div><span class="pill pill-blue">SAMPLE DETECTION</span></div><div class="launcher-grid" style="margin-top:13px">${launchers.map((launcher) => `<div class="launcher-item"><span class="launcher-initial">${launcher.initial}</span><span class="launcher-copy"><strong>${escapeHTML(launcher.name)}</strong><small>${escapeHTML(launcher.detail)}</small></span><span class="launcher-status ${launcher.found ? '' : 'not-found'}">${launcher.found ? 'Example' : '—'}</span></div>`).join('')}</div></article>
        <article class="card card-pad"><div class="card-heading"><div><h2>Memory allocation</h2><p>Leave enough RAM for Windows, the launcher, and recording tools.</p></div><span class="pill ${recommended ? 'pill-green' : 'pill-orange'}">${recommended ? 'In a sensible range' : 'Review allocation'}</span></div><div class="ram-allocation"><div class="ram-allocation-top"><span class="label-caps">Minecraft maximum heap · sample</span><strong id="ramOutput">${state.minecraftRam} GB</strong></div><input class="ram-range" id="ramSlider" data-ram-slider type="range" min="2" max="${maxRam}" step="1" value="${state.minecraftRam}" aria-label="Minecraft memory allocation" style="--range-fill:${((state.minecraftRam - 2) / (maxRam - 2)) * 100}%"><div class="ram-range-labels"><span>2 GB</span><span>6–8 GB suggested</span><span>${maxRam} GB</span></div></div><div class="jvm-box"><code id="jvmArgs">${escapeHTML(args)}</code><button class="jvm-copy" type="button" data-action="copy-jvm" aria-label="Copy JVM arguments">${icon('code')}</button></div><div class="inline-note" style="margin-top:9px">${icon('info')}Only a starting point. Avoid allocating most of system RAM; memory needs depend on mods, version, and shaders.</div></article>
      </div>
      <div class="content-stack">
        <article class="card card-pad"><div class="card-heading"><div><h2>Java runtime guidance</h2><p>Confirm the runtime in your launcher before changing it.</p></div><span class="pill pill-purple">EXAMPLE</span></div><div class="info-pair" style="margin-top:10px"><span>Suggested runtime</span><strong>Java 21 · 1.20.5+</strong></div><div class="info-pair"><span>Legacy versions</span><strong>Java 17 / 8*</strong></div><div class="info-pair"><span>Example installed</span><strong>OpenJDK 21.0.3</strong></div><div class="inline-note" style="margin-top:10px">${icon('info')}*Check the exact Minecraft version and mod loader. This is general guidance, not an installed-Java scan.</div></article>
        <article class="card card-pad"><div class="card-heading"><div><h2>Java argument preset</h2><p>Keep flags short and test one change at a time.</p></div></div><div class="service-filter" style="margin-top:13px"><button type="button" class="filter-chip ${state.jvmPreset === 'Balanced' ? 'active' : ''}" data-jvm-preset="Balanced">Balanced</button><button type="button" class="filter-chip ${state.jvmPreset === 'Minimal' ? 'active' : ''}" data-jvm-preset="Minimal">Minimal</button></div><div class="divider"></div><div class="inline-note">${icon('shield')}Avoid copy-pasted “magic” flags that can make garbage collection or compatibility worse.</div></article>
        <article class="card card-pad"><div class="card-heading"><div><h2>Play profile</h2><p>Set a recommendation for this preview.</p></div></div><div style="margin-top:6px">${minecraftProfiles.map((profile) => `<div class="feature-row"><span class="profile-card-icon ${profile.color}" style="width:27px;height:27px;flex:0 0 27px">${icon(profile.icon)}</span><span class="feature-copy"><strong>${escapeHTML(profile.label)}</strong><small>${escapeHTML(profile.desc)}</small></span><button class="button ${state.minecraftProfile === profile.id ? 'button-secondary' : 'button-quiet'} button-small" type="button" data-minecraft-profile="${escapeHTML(profile.id)}">${state.minecraftProfile === profile.id ? 'Selected' : 'Choose'}</button></div>`).join('')}</div></article>
        <article class="card card-pad"><div class="card-heading"><div><h2>Process & background review</h2><p>Use Normal priority and close only apps you recognize.</p></div></div><div class="feature-row"><span class="feature-copy"><strong>Minecraft process priority</strong><small>Normal is the safe baseline; High can reduce desktop responsiveness.</small></span><button class="button button-quiet button-small" type="button" data-action="priority-review">Review</button></div><div class="feature-row"><span class="feature-copy"><strong>Background app cleanup</strong><small>Save work first; do not terminate security, audio, or driver processes.</small></span><button class="button button-quiet button-small" type="button" data-action="background-review">Review</button></div></article>
        <div class="preview-callout">${icon('alert')}<span><strong>FPS is hardware- and game-dependent.</strong> No FPS promise, process cleanup, priority changes, or Java installation occurs here.</span></div>
      </div>
    </section>`;
}

function renderNetwork() {
  const result = state.networkResult || { latency: '24', jitter: '3', loss: '0.2' };
  const dnsOptions = [
    { name: 'Cloudflare', address: '1.1.1.1 · 1.0.0.1', tag: 'Privacy focused' },
    { name: 'Google DNS', address: '8.8.8.8 · 8.8.4.4', tag: 'Widely available' },
    { name: 'Quad9', address: '9.9.9.9 · 149.112.112.112', tag: 'Security focused' },
  ];
  return `${pageHeader('Network Optimizer', 'Benchmark first, compare results, and keep an undo path. No blind TCP registry tweaks.', 'NETWORK TOOLS', `<button class="button button-primary" type="button" data-action="run-benchmark">${icon('activity')} ${state.networkRunning ? 'Testing…' : 'Run latency test'}</button>`)}
    <section class="content-grid">
      <div class="content-stack">
        <article class="card card-pad"><div class="card-heading"><div><h2>Latency lab</h2><p>Illustrative values only · not a real network test</p></div><span class="pill pill-blue">SAMPLE</span></div><div class="latency-grid" style="margin-top:14px"><div class="latency-stat"><span>Latency</span><strong>${escapeHTML(result.latency)}<small>ms</small></strong></div><div class="latency-stat"><span>Jitter</span><strong>${escapeHTML(result.jitter)}<small>ms</small></strong></div><div class="latency-stat"><span>Packet loss</span><strong>${escapeHTML(result.loss)}<small>%</small></strong></div></div>${state.networkRunning ? progressMarkup('network', state.networkProgress, 'Running sample network benchmark…') : ''}<div class="divider"></div><div class="inline-note">${icon('info')}Real latency depends on server location, Wi-Fi quality, routing, and time of day. Compare the same endpoint before and after any change.</div></article>
        <article class="card card-pad"><div class="card-heading"><div><h2>Network adapter</h2><p>Example adapter information · not read from Windows</p></div><span class="pill pill-green">Connected · sample</span></div><div class="info-pair" style="margin-top:8px"><span>Adapter</span><strong>Intel Ethernet I219-V</strong></div><div class="info-pair"><span>Link speed</span><strong>1.0 Gbps</strong></div><div class="info-pair"><span>MTU</span><strong>1500 bytes</strong></div><div class="info-pair"><span>Power saving</span><strong>Default / unknown</strong></div></article>
      </div>
      <div class="content-stack">
        <article class="card card-pad"><div class="card-heading"><div><h2>DNS profile</h2><p>Select a provider to compare; nothing is applied.</p></div><span class="pill pill-orange">PREVIEW</span></div><div style="margin-top:12px">${dnsOptions.map((option) => `<button type="button" class="network-profile ${state.dnsProfile === option.name ? 'selected' : ''}" data-dns="${escapeHTML(option.name)}"><span class="radio-mark"></span><span class="network-profile-copy"><strong>${escapeHTML(option.name)}</strong><small>${escapeHTML(option.address)}</small></span><span class="network-profile-tag">${escapeHTML(option.tag)}</span></button>`).join('')}</div><button class="button button-secondary button-wide" style="margin-top:11px" type="button" data-action="apply-dns">Preview DNS selection</button><div class="inline-note" style="margin-top:10px">${icon('shield')}A DNS change may not reduce game latency. Always record the previous adapter settings first.</div></article>
        <article class="card card-pad"><div class="card-heading"><div><h2>Advanced actions</h2><p>Destructive or disconnecting actions require explicit review.</p></div></div><div class="feature-row"><span class="feature-copy"><strong>Flush DNS cache</strong><small>Clears the local resolver cache.</small></span><button class="button button-quiet button-small" type="button" data-action="flush-dns">Review</button></div><div class="feature-row"><span class="feature-copy"><strong>Winsock / TCP reset</strong><small>Can disconnect apps and require a restart.</small></span><button class="button button-quiet button-small" type="button" data-action="network-reset">Review</button></div><div class="feature-row"><span class="feature-copy"><strong>Gaming network profile</strong><small>Compare adapter power settings and latency before/after.</small></span><button class="button button-quiet button-small" type="button" data-action="gaming-network">Review</button></div><div class="preview-callout" style="margin-top:10px">${icon('alert')}<span><strong>No blind tuning.</strong> TCP registry values are not changed by this preview.</span></div></article>
      </div>
    </section>`;
}

function hardwareTabButton(tab) {
  return `<button class="tab-button ${state.hardwareTab === tab ? 'active' : ''}" type="button" data-hardware-tab="${tab}" aria-pressed="${state.hardwareTab === tab}">${tab}</button>`;
}

function renderCpuHardware() {
  return `<article class="card hardware-hero"><div class="hardware-main"><span class="icon-box blue">${icon('cpu')}</span><span><h3>Intel Core i5-7500</h3><p>Example processor profile · 7th Gen Intel Core</p></span></div><span class="pill pill-blue">SAMPLE HARDWARE</span></article>
    <div class="hardware-grid section-block" style="margin-top:10px"><div class="hardware-detail"><label>Cores / threads</label><strong>4 cores · 4 threads</strong><small>Example specification</small></div><div class="hardware-detail"><label>Base / boost frequency</label><strong>3.40 / up to 3.80 GHz</strong><small>Varies by power, temperature, workload</small></div><div class="hardware-detail"><label>Virtualization</label><strong>Enabled · sample</strong><small>Verify in Task Manager or firmware</small></div><div class="hardware-detail"><label>Power mode</label><strong>Balanced · sample</strong><small>Avoid forcing maximum power by default</small></div></div>
    <article class="card card-pad section-block"><div class="card-heading"><div><h2>CPU recommendations</h2><p>Measure the bottleneck before changing process behavior.</p></div></div><div class="feature-row"><span class="icon-box lime">${icon('activity')}</span><span class="feature-copy"><strong>Background process review</strong><small>Sort by CPU usage in Task Manager while your game is open.</small></span><span class="pill pill-green">Safe check</span></div><div class="feature-row"><span class="icon-box blue">${icon('battery')}</span><span class="feature-copy"><strong>Power plan</strong><small>Balanced is usually a sensible default on a desktop; compare temperatures and clocks.</small></span><button class="button button-quiet button-small" type="button" data-action="priority-review">Review</button></div></article>`;
}

function renderGpuHardware() {
  return `<article class="card hardware-hero"><div class="hardware-main"><span class="icon-box orange">${icon('gpu')}</span><span><h3>NVIDIA GeForce GTX 1050 Ti</h3><p>Example graphics card · 4 GB VRAM</p></span></div><span class="pill pill-blue">SAMPLE HARDWARE</span></article>
    <div class="hardware-grid section-block" style="margin-top:10px"><div class="hardware-detail"><label>Vendor</label><strong>NVIDIA</strong><small>Example device</small></div><div class="hardware-detail"><label>Driver</label><strong>Version not verified</strong><small>Open vendor software to check updates</small></div><div class="hardware-detail"><label>GPU scheduling</label><strong>Check Windows & driver support</strong><small>Availability depends on OS and driver</small></div><div class="hardware-detail"><label>Shader cache</label><strong>Review in driver settings</strong><small>Clearing can cause temporary stutter while it rebuilds</small></div></div>
    <article class="card card-pad section-block"><div class="card-heading"><div><h2>GPU profile notes</h2><p>Do not promise higher FPS from a toggle alone.</p></div></div><div class="feature-row"><span class="icon-box orange">${icon('gamepad')}</span><span class="feature-copy"><strong>Per-game profile</strong><small>Use the GPU vendor control panel to adjust one game at a time.</small></span><span class="pill pill-orange">Manual review</span></div><div class="feature-row"><span class="icon-box purple">${icon('activity')}</span><span class="feature-copy"><strong>Background GPU apps</strong><small>Check overlays, browsers, capture tools, and hardware acceleration.</small></span><span class="pill pill-blue">Diagnostic</span></div></article>`;
}

function renderBiosHardware() {
  const rows = [
    ['CPU virtualization', 'Enabled', 'Useful for virtual machines and some security features. Confirm in Task Manager or UEFI.'],
    ['TPM 2.0', 'Enabled', 'Windows security requirement on supported systems; do not clear TPM as a performance tweak.'],
    ['Secure Boot', 'Enabled', 'Helps verify the boot chain. Changing it can affect encryption and boot configuration.'],
    ['Resizable BAR', 'Not supported', 'Depends on the CPU, board, GPU, firmware, and driver combination.'],
    ['XMP / EXPO memory profile', 'Not reported', 'Review the motherboard manual and memory stability; never enable blindly.'],
    ['Above 4G decoding', 'Recommended', 'May be relevant for GPU features; verify board support and firmware options.'],
    ['Boot mode', 'UEFI', 'Example device status; a Legacy-to-UEFI conversion is not performed here.'],
    ['BIOS / motherboard', 'B250 board · version unknown', 'Example profile only; check the manufacturer before any firmware update.'],
  ];
  return `<article class="card card-pad"><div class="card-heading"><div><h2>BIOS Advisor</h2><p>Read-only recommendations. No firmware flashing or automatic overclocking.</p></div><span class="pill pill-green">ADVISORY ONLY</span></div><div style="margin-top:8px">${rows.map(([name, status, note]) => `<div class="advisor-row"><div><strong>${escapeHTML(name)}</strong><small>${escapeHTML(note)}</small></div><span class="pill ${status === 'Enabled' || status === 'UEFI' ? 'pill-green' : status === 'Recommended' ? 'pill-blue' : status === 'Not supported' ? 'pill-orange' : ''} advisor-status">${escapeHTML(status)}</span></div>`).join('')}</div><div class="preview-callout" style="margin-top:12px">${icon('alert')}<span><strong>Never flash BIOS or change memory/voltage settings automatically.</strong> Incorrect firmware or unstable memory settings can prevent booting.</span></div></article>`;
}

function renderHardware() {
  let content = renderCpuHardware();
  if (state.hardwareTab === 'GPU') content = renderGpuHardware();
  if (state.hardwareTab === 'BIOS') content = renderBiosHardware();
  return `${pageHeader('Hardware & BIOS Advisor', 'A read-only guide for CPU, GPU, and firmware checks — designed to avoid risky automatic changes.', 'HARDWARE INSIGHTS', `<span class="pill pill-blue">EXAMPLE PC PROFILE</span>`)}<div class="tab-row" role="tablist" aria-label="Hardware categories">${['CPU', 'GPU', 'BIOS'].map(hardwareTabButton).join('')}</div>${content}`;
}

function startupTableHTML() {
  const query = state.startupSearch.trim().toLowerCase();
  const filtered = state.startup.filter((item) => !query || `${item.name} ${item.publisher} ${item.source}`.toLowerCase().includes(query));
  if (!filtered.length) return `<div class="empty-state">No startup entries match “${escapeHTML(state.startupSearch)}”.</div>`;
  return `<div class="table-wrap"><table class="data-table"><thead><tr><th>Application</th><th>Impact</th><th>Entry</th><th>Status</th><th style="text-align:right">Actions</th></tr></thead><tbody>${filtered.map((item) => `
    <tr><td><span class="app-name-cell"><span class="app-monogram">${escapeHTML(item.monogram)}</span><span><strong>${escapeHTML(item.name)}</strong><small>${escapeHTML(item.publisher)}</small></span></span></td>
    <td><span class="impact ${item.impact.toLowerCase()}"><i></i>${escapeHTML(item.impact)}</span></td><td>${escapeHTML(item.source)}</td>
    <td><span class="pill ${item.enabled ? 'pill-green' : ''}">${item.enabled ? 'Enabled' : 'Disabled'}</span></td>
    <td><div class="table-actions"><button class="button ${item.enabled ? 'button-quiet' : 'button-secondary'} button-small" type="button" data-startup-toggle="${item.id}">${item.enabled ? 'Disable' : 'Enable'}</button><button class="button button-quiet button-small" type="button" data-app-open="${item.id}" aria-label="Open ${escapeHTML(item.name)} location">Open</button><button class="button button-quiet button-small" type="button" data-app-search="${item.id}" aria-label="Search online for ${escapeHTML(item.name)}">Search</button></div></td></tr>`).join('')}</tbody></table></div>`;
}

function renderStartup() {
  const enabledCount = state.startup.filter((item) => item.enabled).length;
  const highCount = state.startup.filter((item) => item.enabled && item.impact === 'High').length;
  return `${pageHeader('Startup Manager', 'Review impact and startup state for each app. A native build should back up entries before editing them.', 'WINDOWS MANAGEMENT', `<button class="button button-quiet" type="button" data-action="startup-defaults">${icon('refresh')} Restore defaults</button>`)}
    <section class="metric-grid" style="margin-top:0;margin-bottom:13px"><article class="card metric-card"><div class="metric-card-top"><span class="metric-caption">Enabled entries</span><span class="metric-icon lime">${icon('rocket')}</span></div><div class="metric-value">${enabledCount}<small>apps</small></div><div class="metric-detail"><span>Example list</span><strong>of ${state.startup.length}</strong></div></article><article class="card metric-card"><div class="metric-card-top"><span class="metric-caption">High impact</span><span class="metric-icon orange">${icon('activity')}</span></div><div class="metric-value">${highCount}<small>apps</small></div><div class="metric-detail"><span>Enabled high-impact items</span><strong>Review</strong></div></article><article class="card metric-card"><div class="metric-card-top"><span class="metric-caption">Changes made</span><span class="metric-icon blue">${icon('history')}</span></div><div class="metric-value">0<small>system</small></div><div class="metric-detail"><span>Preview does not edit startup</span><strong>—</strong></div></article><article class="card metric-card"><div class="metric-card-top"><span class="metric-caption">Source</span><span class="metric-icon purple">${icon('monitor')}</span></div><div class="metric-value" style="font-size:16px">Example PC</div><div class="metric-detail"><span>Not detected from device</span><strong>DEMO</strong></div></article></section>
    <div class="table-toolbar"><label class="search-field">${icon('search')}<input id="startupSearch" data-startup-search type="search" placeholder="Search apps or publishers…" value="${escapeHTML(state.startupSearch)}" aria-label="Search startup apps"></label><span class="table-toolbar-meta">${enabledCount} enabled · ${state.startup.length} sample entries</span></div>
    <div id="startupTableHost">${startupTableHTML()}</div>
    <div class="preview-callout" style="margin-top:13px">${icon('info')}<span><strong>Preview only:</strong> Enable/Disable updates this mock table in memory. No registry key, scheduled task, or Startup folder is touched.</span></div>`;
}

function servicesTableHTML() {
  const services = state.services.filter((service) => state.serviceFilter === 'All services' || (state.serviceFilter === 'Optional review' && ['Conditional', 'Review vendor'].includes(service.recommendation)) || (state.serviceFilter === 'Microsoft only' && service.publisher === 'Microsoft'));
  return `<div class="table-wrap"><table class="data-table"><thead><tr><th>Service</th><th>State</th><th>Startup type</th><th>Publisher</th><th>Recommendation</th><th></th></tr></thead><tbody>${services.map((service) => `<tr><td><span class="app-name-cell"><span class="app-monogram">${service.publisher === 'Microsoft' ? 'W' : '3P'}</span><span><strong>${escapeHTML(service.name)}</strong><small>${escapeHTML(service.service)}</small></span></span></td><td><span class="pill ${service.state === 'Running' ? 'pill-green' : ''}">${escapeHTML(service.state)}</span></td><td>${escapeHTML(service.startup)}</td><td>${escapeHTML(service.publisher)}</td><td><span class="pill ${service.recommendation === 'Keep default' ? 'pill-green' : 'pill-orange'}">${escapeHTML(service.recommendation)}</span></td><td><button class="button button-quiet button-small" type="button" data-service-review="${service.id}">Review</button></td></tr>`).join('')}</tbody></table></div>`;
}

function renderServices() {
  const filters = ['All services', 'Optional review', 'Microsoft only'];
  return `${pageHeader('Services Manager', 'Advanced, read-only service guidance. Never disable Windows services at random.', 'WINDOWS MANAGEMENT', `<span class="pill pill-orange">ADMIN ACTIONS DISABLED</span>`)}
    <div class="recommendation-card" style="margin-bottom:13px"><span class="icon-box blue">${icon('shield')}</span><span><strong>Safe defaults are kept by design.</strong><p>Service dependencies vary by PC. Recommendations are informational; Windows restore points and a service-state backup should come first in any native app.</p></span></div>
    <div class="table-toolbar"><div class="service-filter">${filters.map((filter) => `<button class="filter-chip ${state.serviceFilter === filter ? 'active' : ''}" type="button" data-service-filter="${escapeHTML(filter)}">${escapeHTML(filter)}</button>`).join('')}</div><span class="table-toolbar-meta">${state.services.length} example services · not enumerated from Windows</span></div>
    ${servicesTableHTML()}
    <div class="preview-callout" style="margin-top:13px">${icon('alert')}<span><strong>No service changes are applied.</strong> Use the service publisher's documentation and confirm feature dependencies before changing startup type.</span></div>`;
}

function renderPrivacy() {
  const options = [
    { key: 'advertisingId', title: 'Advertising ID', desc: 'Optional identifier used by apps for personalized advertising. Sample state only.', badge: 'Optional' },
    { key: 'diagnostics', title: 'Optional diagnostic data', desc: 'Windows diagnostics choices can affect feature diagnostics and support.', badge: 'Review Windows settings' },
    { key: 'activityHistory', title: 'Activity history', desc: 'Review local history and sync controls based on your own workflow.', badge: 'Optional' },
    { key: 'backgroundApps', title: 'Background app permissions', desc: 'Available controls depend on Windows version and the individual app.', badge: 'Per app' },
  ];
  return `${pageHeader('Privacy Controls', 'Understand optional Windows privacy settings before deciding. No privacy preference is changed here.', 'PRIVACY & CONTROL', `<button class="button button-secondary" type="button" data-action="privacy-guide">${icon('book')} Privacy guide</button>`)}
    <section class="content-grid">
      <article class="card card-pad"><div class="card-heading"><div><h2>Optional controls</h2><p>Sample states are not read from your Windows account.</p></div><span class="pill pill-blue">LOCAL PREVIEW</span></div><div style="margin-top:7px">${options.map((option) => `<div class="feature-row"><span class="icon-box ${option.key === 'advertisingId' ? 'purple' : option.key === 'diagnostics' ? 'blue' : 'lime'}">${icon(option.key === 'advertisingId' ? 'target' : option.key === 'diagnostics' ? 'activity' : option.key === 'activityHistory' ? 'history' : 'layers')}</span><span class="feature-copy"><strong>${escapeHTML(option.title)}</strong><small>${escapeHTML(option.desc)}</small></span><span class="feature-trailing"><span class="switch-label">${escapeHTML(option.badge)}</span>${switchInput(option.key, state.privacy[option.key], option.title, 'data-privacy-toggle')}</span></div>`).join('')}</div></article>
      <div class="content-stack"><article class="card card-pad"><div class="card-heading"><div><h2>Before you change privacy settings</h2><p>Make a choice that fits your needs.</p></div><span class="icon-box lime">${icon('lock')}</span></div><div class="info-pair" style="margin-top:9px"><span>Start with</span><strong>Windows Settings</strong></div><div class="info-pair"><span>Check scope</span><strong>Per user / per app</strong></div><div class="info-pair"><span>Undo path</span><strong>Record old values</strong></div><div class="inline-note" style="margin-top:10px">${icon('info')}Some diagnostic data is required for updates and device health. Changes may affect app features or support.</div></article><div class="preview-callout">${icon('shield')}<span><strong>Privacy commitment:</strong> this prototype stores no HWID, telemetry, account, or device data. Switches only update this page's sample state.</span></div></div>
    </section>`;
}

function renderDebloat() {
  return `${pageHeader('Debloat', 'Review preinstalled apps one at a time. There is no “Remove everything” button.', 'APP REVIEW', `<span class="pill pill-green">INDIVIDUAL REVIEW</span>`)}
    <div class="recommendation-card" style="margin-bottom:13px"><span class="icon-box lime">${icon('shieldCheck')}</span><span><strong>Keep what you use.</strong><p>Some apps are dependencies for games, widgets, calling, or Microsoft Store features. Review publisher and reinstall options first.</p></span></div>
    <section class="app-catalog-grid">${debloatItems.map((item) => `<article class="catalog-card"><div class="catalog-card-head"><span class="app-name-cell"><span class="app-monogram">${item.name.split(' ').map((word) => word[0]).slice(0, 2).join('')}</span><span><h3>${escapeHTML(item.name)}</h3><small>${escapeHTML(item.publisher)}</small></span></span><span class="pill pill-blue">Sample</span></div><p>${escapeHTML(item.note)}</p><button class="button button-quiet button-small" type="button" data-debloat-review="${item.id}">${icon('eye')} Review app</button></article>`).join('')}</section>
    <div class="preview-callout" style="margin-top:13px">${icon('alert')}<span><strong>Removal is not available in preview.</strong> A production uninstaller should use per-package consent, dependency checks, restore support, and clear reinstall guidance.</span></div>`;
}

function repairTerminal() {
  const task = state.repair;
  const lines = task.log.map((line, index) => `<p class="terminal-line ${line.toLowerCase().includes('preview') || line.toLowerCase().includes('not') ? 'muted' : ''}">${index === task.log.length - 1 && task.running ? '<span class="terminal-cursor">› </span>' : ''}${escapeHTML(line)}</p>`).join('');
  return `<div class="terminal"><div class="terminal-head"><span class="terminal-dots"><i></i><i></i><i></i></span><span class="terminal-title">tharu-repair · preview session</span><span class="pill pill-orange">SIMULATED</span></div><div class="terminal-body">${lines}${task.running ? `<div class="terminal-progress"><div class="terminal-progress-meta"><span data-progress-label="repair">Preview: ${escapeHTML(task.name)}</span><span data-progress-value="repair">${task.progress}%</span></div><div class="meter"><span data-progress="repair" style="width:${task.progress}%"></span></div></div>` : ''}</div></div>`;
}

function renderRepair() {
  return `${pageHeader('System Repair', 'A terminal-style progress preview for common diagnostics. No commands run and no files are modified.', 'DIAGNOSTICS', `<span class="pill pill-orange">SIMULATION ONLY</span>`)}
    <section class="repair-grid">${repairOptions.map((option) => `<article class="repair-card"><div class="repair-card-head"><span class="icon-box ${option.id === 'network-repair' ? 'blue' : option.id === 'chkdsk' ? 'orange' : 'lime'}">${icon(option.icon)}</span><span class="duration">${escapeHTML(option.duration)}</span></div><h3>${escapeHTML(option.name)}</h3><p>${escapeHTML(option.desc)}</p><button class="button button-quiet button-small" type="button" data-repair="${option.id}" ${state.repair.running ? 'disabled' : ''}>${icon('play')} Preview run</button></article>`).join('')}</section>
    <section class="section-block">${repairTerminal()}</section>
    <div class="preview-callout" style="margin-top:13px">${icon('alert')}<span><strong>Nothing is executed.</strong> In production, repair actions must show exact commands, request admin permission only when needed, allow cancellation, and report real exit codes.</span></div>`;
}

function renderRestore() {
  return `${pageHeader('Restore Center', 'A restore-first safety workflow for future native actions. This browser session cannot create a Windows restore point.', 'SAFETY & RECOVERY', `<button class="button button-primary" type="button" data-action="create-restore">${icon('plus')} Create restore point</button>`)}
    <section class="restore-banner"><div class="restore-banner-copy"><span class="icon-box lime">${icon('shieldCheck')}</span><span><h2>Build a safety net before tuning.</h2><p>Native System Restore, registry exports, and file backups require a Windows desktop integration that is not connected in this prototype.</p></span></div><div class="restore-actions"><button class="button button-secondary button-small" type="button" data-action="export-settings">${icon('download')} Export preview JSON</button><button class="button button-quiet button-small" type="button" data-action="backup-settings">${icon('save')} Backup preview settings</button></div></section>
    <section class="restore-center-grid section-block">
      <article class="card card-pad"><div class="section-title"><div><h2>Preview snapshots</h2><p>Browser-only records · these are not Windows restore points.</p></div><span class="pill pill-blue">${state.snapshots.length} LOCAL</span></div><div class="snapshot-list">${state.snapshots.map((snapshot) => `<div class="snapshot-row"><span class="icon-box ${snapshot.id === 'session-start' ? 'blue' : 'lime'}">${icon('history')}</span><span class="snapshot-copy"><strong>${escapeHTML(snapshot.title)}</strong><small>${escapeHTML(snapshot.type)} · ${escapeHTML(snapshot.profile || 'Preview')}</small></span><span class="snapshot-meta">${escapeHTML(snapshot.time)}</span></div>`).join('')}</div>${state.snapshots.length === 0 ? '<div class="empty-state">No preview snapshots yet.</div>' : ''}<div class="divider"></div><button class="button button-danger button-small" type="button" data-action="undo-last">${icon('rotate')} Undo last preview run</button></article>
      <article class="card card-pad"><div class="card-heading"><div><h2>Safe change sequence</h2><p>How the production app should handle risky changes.</p></div></div><div style="margin-top:8px"><div class="restore-step"><span class="restore-step-num">01</span><span class="restore-step-copy"><strong>Create a Windows restore point</strong><small>Request elevation clearly and verify that creation succeeded.</small></span></div><div class="restore-step"><span class="restore-step-num">02</span><span class="restore-step-copy"><strong>Export the exact values being changed</strong><small>Back up targeted settings; avoid broad, undocumented registry exports.</small></span></div><div class="restore-step"><span class="restore-step-num">03</span><span class="restore-step-copy"><strong>Apply one reversible change</strong><small>Show before/after values and record an undo action.</small></span></div><div class="restore-step"><span class="restore-step-num">04</span><span class="restore-step-copy"><strong>Verify and offer Undo</strong><small>Do not report success until the system confirms the change.</small></span></div></div></article>
    </section>
    <div class="preview-callout">${icon('info')}<span><strong>Local-only:</strong> the “Export preview JSON” file contains these interface preferences and the selected profile only. No registry data, HWID, or real device details are exported.</span></div>`;
}

function renderSettings() {
  const settingRows = [
    { key: 'notifications', title: 'In-app notifications', desc: 'Show brief status messages during this preview.' },
    { key: 'startup', title: 'Launch on sign-in', desc: 'A future Windows app could offer this preference with clear consent.' },
    { key: 'compactMode', title: 'Compact dashboard', desc: 'Preview preference only; no data is sent or synced.' },
  ];
  return `${pageHeader('Settings', 'Control local preview preferences and learn what a seller-ready version still needs.', 'APP PREFERENCES', `<button class="button button-quiet" type="button" data-action="export-settings">${icon('download')} Export preview settings</button>`)}
    <section class="settings-grid">
      <article class="card card-pad"><div class="card-heading"><div><h2>Preferences</h2><p>These controls affect only this page session.</p></div><span class="pill pill-blue">LOCAL ONLY</span></div>${settingRows.map((row) => `<div class="setting-row"><span class="setting-row-copy"><strong>${escapeHTML(row.title)}</strong><small>${escapeHTML(row.desc)}</small></span>${switchInput(row.key, state.settings[row.key], row.title, 'data-setting-toggle')}</div>`).join('')}<div class="settings-section"><h3>Privacy and updates</h3><div class="setting-row"><span class="setting-row-copy"><strong>Device activation</strong><small>No license service, HWID binding, or device fingerprinting is implemented.</small></span><span class="pill pill-orange">Not connected</span></div><div class="setting-row"><span class="setting-row-copy"><strong>Automatic updates</strong><small>No updater or crash reporting runs in this prototype.</small></span><button class="button button-quiet button-small" type="button" data-action="check-updates">Check</button></div></div></article>
      <div class="content-stack"><article class="card version-card"><div class="version-logo"><span class="brand-mark">${icon('zap')}</span><span><strong>THARU OPTIMIZER</strong><small>Windows + Minecraft toolkit</small></span></div><p>This is an interactive frontend preview. It uses example hardware and app data, and it does not connect to a Windows service, cloud account, or licensing backend.</p><div class="version-foot"><span>VERSION</span><strong>0.1.0 · PREVIEW</strong></div></article><div class="preview-callout">${icon('shield')}<span><strong>Before selling:</strong> add a signed native backend, transparent UAC prompts, restore verification, secure updates, a privacy policy, and independent safety testing.</span></div><button class="button button-secondary button-wide" type="button" data-action="about">About this preview</button></div>
    </section>`;
}

const pageRenderers = {
  overview: renderOverview,
  cleaner: renderCleaner,
  gaming: renderGaming,
  minecraft: renderMinecraft,
  network: renderNetwork,
  hardware: renderHardware,
  startup: renderStartup,
  services: renderServices,
  privacy: renderPrivacy,
  debloat: renderDebloat,
  repair: renderRepair,
  restore: renderRestore,
  settings: renderSettings,
};

function renderPage() {
  const previouslyFocused = document.activeElement;
  const focusAttributes = [
    'data-cleaner-toggle', 'data-gaming-toggle', 'data-privacy-toggle', 'data-setting-toggle',
    'data-profile', 'data-hardware-tab', 'data-dns', 'data-service-filter', 'data-startup-toggle',
    'data-app-open', 'data-app-search', 'data-repair', 'data-minecraft-profile', 'data-jvm-preset', 'data-nav',
  ];
  const focusAttribute = focusAttributes.find((attribute) => previouslyFocused?.hasAttribute?.(attribute));
  const focusValue = focusAttribute ? previouslyFocused.getAttribute(focusAttribute) : null;
  const focusId = previouslyFocused?.id || null;

  updatePageChrome();
  pageContent.innerHTML = (pageRenderers[state.page] || renderOverview)();

  let replacement = focusId ? document.getElementById(focusId) : null;
  if (!replacement && focusAttribute) {
    replacement = $$(`[${focusAttribute}]`).find((node) => node.getAttribute(focusAttribute) === focusValue) || null;
  }
  replacement?.focus({ preventScroll: true });
}

function navigate(page) {
  if (!pageRenderers[page]) return;
  state.page = page;
  renderPage();
  closeMobileMenu();
  pageContent.focus({ preventScroll: true });
  window.scrollTo({ top: 0, behavior: 'smooth' });
}

function showToast(message, kind = 'success') {
  const node = document.createElement('div');
  node.className = `toast ${kind === 'error' ? 'error' : ''}`;
  node.innerHTML = `${icon(kind === 'error' ? 'alert' : 'check')}<span>${escapeHTML(message)}</span>`;
  toastRoot.appendChild(node);
  window.setTimeout(() => {
    node.style.opacity = '0';
    node.style.transform = 'translateY(5px)';
    window.setTimeout(() => node.remove(), 220);
  }, 3600);
}

function closeModal() {
  modalRoot.innerHTML = '';
  state.modalConfirm = null;
}

function showModal({ title, description, body, confirmText = 'Continue', confirmClass = 'button-primary', onConfirm = () => {}, cancelText = 'Cancel' }) {
  state.modalConfirm = onConfirm;
  modalRoot.innerHTML = `<div class="modal-backdrop" data-modal-backdrop><section class="modal-dialog" role="dialog" aria-modal="true" aria-labelledby="modalTitle" tabindex="-1"><div class="modal-header"><div><h2 id="modalTitle">${escapeHTML(title)}</h2><p>${escapeHTML(description || '')}</p></div><button class="modal-close" type="button" data-action="modal-close" aria-label="Close dialog">${icon('close')}</button></div><div class="modal-body">${body || ''}</div><div class="modal-footer"><button class="button button-quiet" type="button" data-action="modal-close">${escapeHTML(cancelText)}</button><button class="button ${confirmClass}" type="button" data-action="modal-confirm">${escapeHTML(confirmText)}</button></div></section></div>`;
  window.setTimeout(() => $('.modal-dialog', modalRoot)?.focus(), 0);
}

function addSnapshot(title = 'Before optimization preview') {
  const snapshot = {
    id: `snapshot-${Date.now()}-${Math.round(Math.random() * 1000)}`,
    title,
    time: new Intl.DateTimeFormat('en-US', { month: 'short', day: 'numeric', hour: 'numeric', minute: '2-digit' }).format(new Date()),
    type: 'Browser-only snapshot',
    profile: state.profile,
  };
  state.snapshots.unshift(snapshot);
  state.activity.unshift({ title: 'Preview snapshot created', detail: `${state.profile} profile · browser only`, time: 'Just now', icon: 'history' });
}

function openRestoreModal(afterCreate = null) {
  showModal({
    title: 'Create a restore point?',
    description: 'Safety step · browser preview only',
    body: `<div class="preview-callout">${icon('alert')}<span><strong>This does not create a Windows System Restore point.</strong> It creates a small in-memory preview record only. A native app must request Windows permissions and confirm the real restore point succeeded.</span></div><div class="modal-summary"><div class="modal-summary-row"><span>Profile</span><strong>${escapeHTML(state.profile)}</strong></div><div class="modal-summary-row"><span>Stored on</span><strong>This page session only</strong></div><div class="modal-summary-row"><span>System changes</span><strong>None</strong></div></div>`,
    confirmText: 'Create preview record',
    onConfirm: () => {
      addSnapshot('Before optimization preview');
      if (afterCreate) afterCreate();
      else {
        renderPage();
        showToast('Browser-only snapshot added. Windows was not changed.');
      }
    },
  });
}

function openOptimizeModal() {
  const selectedSize = formatSize(getSelectedCleanerSize());
  showModal({
    title: 'Review optimization preview',
    description: `Profile: ${state.profile} · no changes will be applied`,
    body: `<p>This walkthrough will create a browser-only snapshot, then record a simulated run. It will not clean files, edit Windows settings, change services, or close background apps.</p><div class="modal-summary"><div class="modal-summary-row"><span>Cleaner items selected</span><strong>${escapeHTML(selectedSize)}</strong></div><div class="modal-summary-row"><span>Profile checklist</span><strong>${(profileChecklists[state.profile] || []).length} review items</strong></div><div class="modal-summary-row"><span>Undo support</span><strong>Preview history only</strong></div></div><div class="preview-callout">${icon('shield')}<span><strong>Restore-first:</strong> the preview records a local snapshot before continuing. A native build must create and verify a real Windows restore point.</span></div>`,
    confirmText: 'Run preview',
    onConfirm: () => {
      addSnapshot('Before optimization preview');
      state.lastRun = Date.now();
      state.activity.unshift({ title: 'Optimization preview completed', detail: `${state.profile} profile · no Windows settings changed`, time: 'Just now', icon: 'sparkles' });
      renderPage();
      showToast('Preview complete · no Windows settings were changed.');
    },
  });
}

function runDemoProgress(kind, duration = 1800) {
  if (kind === 'scan' && state.scanRunning) return showToast('A preview scan is already running.');
  if (kind === 'network' && state.networkRunning) return showToast('A sample latency test is already running.');
  if (kind === 'repair' && state.repair.running) return showToast('A simulated repair is already running.');
  if (kind === 'scan') { state.scanRunning = true; state.scanProgress = 0; }
  if (kind === 'network') { state.networkRunning = true; state.networkProgress = 0; }
  if (kind === 'repair') { state.repair.running = true; state.repair.progress = 0; }
  renderPage();
  const start = Date.now();
  const interval = window.setInterval(() => {
    const progress = Math.min(100, Math.round(((Date.now() - start) / duration) * 100));
    if (kind === 'scan') state.scanProgress = progress;
    if (kind === 'network') state.networkProgress = progress;
    if (kind === 'repair') state.repair.progress = progress;
    $$(`[data-progress="${kind}"]`).forEach((bar) => { bar.style.width = `${progress}%`; });
    $$(`[data-progress-value="${kind}"]`).forEach((value) => { value.textContent = `${progress}%`; });
    if (progress >= 100) {
      window.clearInterval(interval);
      if (kind === 'scan') { state.scanRunning = false; state.cleanerScanned = true; }
      if (kind === 'network') {
        state.networkRunning = false;
        state.networkResult = { latency: '24', jitter: '3', loss: '0.2' };
      }
      if (kind === 'repair') {
        state.repair.running = false;
        state.repair.progress = 100;
        state.repair.log = ['THARU SYSTEM REPAIR · PREVIEW CONSOLE', `Preview flow completed: ${state.repair.name}.`, 'No Windows command was executed.', 'No files, settings, or system components were modified.'];
      }
      renderPage();
      if (kind === 'scan') showToast('Preview scan complete · sample categories are ready to review.');
      if (kind === 'network') showToast('Sample benchmark complete · values are illustrative only.');
      if (kind === 'repair') showToast(`${state.repair.name} preview finished · no system command ran.`);
    }
  }, 60);
}

function exportPreviewSettings() {
  const payload = {
    product: 'THARU OPTIMIZER',
    format: 'preview-preferences',
    version: '0.1.0',
    exportedAt: new Date().toISOString(),
    note: 'Preview-only UI preferences. This is not a registry export, Windows restore point, or system backup.',
    profile: state.profile,
    minecraftProfile: state.minecraftProfile,
    minecraftRamGb: state.minecraftRam,
    jvmPreset: state.jvmPreset,
    dnsProfile: state.dnsProfile,
    cleanerSelection: state.cleanerSelection,
    privacyPreview: state.privacy,
    settings: state.settings,
    startupPreview: state.startup.map(({ id, enabled }) => ({ id, enabled })),
  };
  const blob = new Blob([JSON.stringify(payload, null, 2)], { type: 'application/json' });
  const url = URL.createObjectURL(blob);
  const anchor = document.createElement('a');
  anchor.href = url;
  anchor.download = 'tharu-preview-settings.json';
  document.body.appendChild(anchor);
  anchor.click();
  anchor.remove();
  URL.revokeObjectURL(url);
  showToast('Preview preferences exported as JSON. No device data included.');
}

function reviewStartupItem(id) {
  const item = state.startup.find((entry) => entry.id === id);
  if (!item) return;
  item.enabled = !item.enabled;
  renderPage();
  showToast(`Preview only: ${item.name} marked ${item.enabled ? 'enabled' : 'disabled'} in this table.`);
}

function openServiceReview(id) {
  const service = state.services.find((entry) => entry.id === id);
  if (!service) return;
  showModal({
    title: `Review ${service.name}`,
    description: `${service.publisher} · ${service.service}`,
    body: `<p>${escapeHTML(service.note)}</p><div class="modal-summary"><div class="modal-summary-row"><span>Current sample state</span><strong>${escapeHTML(service.state)}</strong></div><div class="modal-summary-row"><span>Startup type sample</span><strong>${escapeHTML(service.startup)}</strong></div><div class="modal-summary-row"><span>Guidance</span><strong>${escapeHTML(service.recommendation)}</strong></div></div><div class="preview-callout">${icon('alert')}<span>No service is changed here. A native service manager should record the exact start type, create recovery instructions, and confirm dependencies first.</span></div>`,
    confirmText: 'Acknowledge recommendation',
    confirmClass: 'button-secondary',
    onConfirm: () => showToast(`${service.name} recommendation acknowledged · no service changes made.`),
  });
}

function openDebloatReview(id) {
  const item = debloatItems.find((entry) => entry.id === id);
  if (!item) return;
  showModal({
    title: `Review ${item.name}`,
    description: `Sample app catalog · ${item.publisher}`,
    body: `<p>${escapeHTML(item.note)}</p><div class="modal-summary"><div class="modal-summary-row"><span>Category</span><strong>${escapeHTML(item.category)}</strong></div><div class="modal-summary-row"><span>Publisher</span><strong>${escapeHTML(item.publisher)}</strong></div><div class="modal-summary-row"><span>Removal</span><strong>Not available in preview</strong></div></div><div class="preview-callout">${icon('info')}<span>Before removal, verify the package identity, check dependencies, create a restore point, and confirm how the app can be reinstalled.</span></div>`,
    confirmText: 'Add to review list',
    confirmClass: 'button-secondary',
    onConfirm: () => showToast(`${item.name} added to this preview's review flow. No app was removed.`),
  });
}

function openAbout() {
  showModal({
    title: 'About this preview',
    description: 'THARU OPTIMIZER · Windows + Minecraft toolkit',
    body: `<div class="preview-callout">${icon('info')}<span><strong>This is a frontend prototype.</strong> Hardware readings, launcher detection, disk sizes, and service/startup tables are sample data.</span></div><div class="modal-summary"><div class="modal-summary-row"><span>System integration</span><strong>Not connected</strong></div><div class="modal-summary-row"><span>Network requests</span><strong>None from app logic</strong></div><div class="modal-summary-row"><span>Local changes</span><strong>Preview state only</strong></div><div class="modal-summary-row"><span>Device fingerprinting</span><strong>Not implemented</strong></div></div><p>All Optimize, Cleaner, Repair, service, privacy, and network actions are demonstrations. This page does not execute PowerShell, delete files, or edit the registry.</p>`,
    confirmText: 'Got it',
    confirmClass: 'button-secondary',
    cancelText: 'Close',
  });
}

function showGenericReview(title, detail, confirm = 'Continue preview') {
  showModal({
    title,
    description: 'Preview mode · no Windows action will run',
    body: `<div class="preview-callout">${icon('alert')}<span>${escapeHTML(detail)}</span></div><div class="modal-summary"><div class="modal-summary-row"><span>System changes</span><strong>None</strong></div><div class="modal-summary-row"><span>Required in native version</span><strong>Permission + backup + undo</strong></div></div>`,
    confirmText: confirm,
    confirmClass: 'button-secondary',
    onConfirm: () => showToast('Preview acknowledged · Windows was not changed.'),
  });
}

function handleAction(action, element) {
  switch (action) {
    case 'toggle-menu': {
      const sidebar = $('#sidebar');
      if (!sidebar.classList.contains('open')) {
        sidebar.classList.add('open');
        const backdrop = document.createElement('div');
        backdrop.className = 'sidebar-backdrop';
        backdrop.id = 'sidebarBackdrop';
        backdrop.addEventListener('click', closeMobileMenu, { once: true });
        document.body.appendChild(backdrop);
      } else closeMobileMenu();
      break;
    }
    case 'about': openAbout(); break;
    case 'scan-system': runDemoProgress('scan', 1700); break;
    case 'optimize-now': openOptimizeModal(); break;
    case 'create-restore': openRestoreModal(); break;
    case 'modal-close': closeModal(); break;
    case 'modal-confirm': {
      const callback = state.modalConfirm;
      closeModal();
      callback?.();
      break;
    }
    case 'select-safe':
      cleanerItems.forEach((item) => { state.cleanerSelection[item.id] = item.safe; });
      renderPage();
      showToast('Selected categories marked low risk for review. Nothing was removed.');
      break;
    case 'select-all':
      cleanerItems.forEach((item) => { state.cleanerSelection[item.id] = true; });
      renderPage();
      break;
    case 'clear-cleaner-selection':
      cleanerItems.forEach((item) => { state.cleanerSelection[item.id] = false; });
      renderPage();
      break;
    case 'review-cleanup': {
      const selected = cleanerItems.filter((item) => state.cleanerSelection[item.id]);
      const size = formatSize(getSelectedCleanerSize());
      showModal({
        title: 'Review selected cleanup items',
        description: `${selected.length} categories · ${size} estimated in sample data`,
        body: `<div class="modal-summary">${selected.slice(0, 8).map((item) => `<div class="modal-summary-row"><span>${escapeHTML(item.name)}</span><strong>${formatSize(item.mb)}</strong></div>`).join('')}${selected.length > 8 ? `<div class="modal-summary-row"><span>Additional categories</span><strong>${selected.length - 8} more</strong></div>` : ''}<div class="modal-summary-row"><span>Total selected</span><strong>${size}</strong></div></div><div class="preview-callout">${icon('alert')}<span><strong>Preview only.</strong> Confirming does not delete any file. A real cleaner must re-scan file paths, skip in-use or protected files, and show a recoverable backup path.</span></div>`,
        confirmText: 'Continue preview',
        confirmClass: 'button-secondary',
        onConfirm: () => showToast(`Cleanup review complete · ${size} sample estimate, no files deleted.`),
      });
      break;
    }
    case 'apply-profile':
      showModal({
        title: `Preview ${state.profile} profile?`,
        description: 'Restore-first confirmation · no settings will be applied',
        body: `<p>This records a browser-only snapshot and walks through the selected profile checklist.</p><div class="modal-summary">${(profileChecklists[state.profile] || []).map((item) => `<div class="modal-summary-row"><span>${escapeHTML(item)}</span><strong>Review</strong></div>`).join('')}<div class="modal-summary-row"><span>Windows changes</span><strong>None</strong></div></div>`,
        confirmText: 'Preview profile',
        onConfirm: () => {
          addSnapshot(`Before ${state.profile} profile preview`);
          state.lastRun = Date.now();
          state.activity.unshift({ title: `${state.profile} profile preview`, detail: 'Checklist reviewed · no system changes', time: 'Just now', icon: 'gamepad' });
          renderPage();
          showToast(`${state.profile} profile preview complete. No system changes made.`);
        },
      });
      break;
    case 'priority-review':
      showGenericReview('Review process priority', 'Changing process priority can make the desktop or audio less responsive. Normal priority is the safe default; test a specific game before considering anything else.', 'Acknowledge');
      break;
    case 'background-review':
      showGenericReview('Review background processes', 'Save active work and close only apps you recognize. Do not terminate antivirus, audio, graphics-driver, or Windows processes to chase a temporary benchmark result.', 'Got it');
      break;
    case 'run-benchmark': runDemoProgress('network', 1900); break;
    case 'apply-dns':
      showGenericReview(`Preview ${state.dnsProfile} DNS`, 'This only selects a provider in the preview. DNS changes can alter connectivity, privacy, and filtering; record your current settings and measure the same endpoint first.', 'Acknowledge');
      break;
    case 'flush-dns':
      showGenericReview('Flush DNS cache?', 'A cache flush is a Windows action that is unavailable in this browser preview. It does not normally improve game server routing or lower distance-based latency.', 'Got it');
      break;
    case 'network-reset':
      showGenericReview('Review network reset', 'Winsock or TCP/IP resets can disconnect applications, alter networking state, and require a restart. Benchmark first and export adapter settings before any native reset.', 'Got it');
      break;
    case 'gaming-network':
      showGenericReview('Review gaming network profile', 'Compare a real latency baseline and packet loss to the same endpoint first. Do not force MTU, power, or TCP values without evidence and a documented undo path.', 'Got it');
      break;
    case 'startup-defaults':
      showModal({
        title: 'Restore sample defaults?',
        description: 'This resets only the startup preview table',
        body: `<p>The sample startup list will return to its original enabled/disabled statuses. No real Windows startup entries are read or changed.</p>`,
        confirmText: 'Restore preview defaults',
        confirmClass: 'button-secondary',
        onConfirm: () => { state.startup = startupDefaults.map((item) => ({ ...item })); state.startupSearch = ''; renderPage(); showToast('Sample startup table restored. Windows was not changed.'); },
      });
      break;
    case 'startup-toggle':
      reviewStartupItem(element.dataset.startupToggle);
      break;
    case 'app-open': {
      const item = state.startup.find((entry) => entry.id === element.dataset.appOpen);
      showGenericReview(`Open ${item?.name || 'app'} location`, 'File location access is not available from a browser. A signed desktop build should reveal the path and publisher before opening it.', 'Got it');
      break;
    }
    case 'app-search': {
      const item = state.startup.find((entry) => entry.id === element.dataset.appSearch);
      if (item) window.open(`https://www.google.com/search?q=${encodeURIComponent(`${item.name} startup impact`)}`, '_blank', 'noopener,noreferrer');
      break;
    }
    case 'service-review': openServiceReview(element.dataset.serviceReview); break;
    case 'service-toggle': {
      const service = state.services.find((entry) => entry.id === element.dataset.serviceToggle);
      if (service) showGenericReview(`Preview service change: ${service.name}`, `${service.note} A real service change requires admin approval, a dependency review, and a recorded restore path.`, 'Acknowledge');
      break;
    }
    case 'privacy-guide':
      showGenericReview('Privacy settings guide', 'Open Windows Settings > Privacy & security to review each control in context. Avoid disabling required diagnostics or features without understanding the impact.', 'Got it');
      break;
    case 'debloat-review': openDebloatReview(element.dataset.debloatReview); break;
    case 'repair': {
      const option = repairOptions.find((item) => item.id === element.dataset.repair);
      if (!option) break;
      state.repair.name = option.name;
      state.repair.log = ['THARU SYSTEM REPAIR · PREVIEW CONSOLE', `Preparing simulated ${option.short} flow…`, 'No system commands have been executed.'];
      runDemoProgress('repair', 2200);
      break;
    }
    case 'create-restore': openRestoreModal(); break;
    case 'undo-last':
      showModal({
        title: 'Undo last preview run?',
        description: 'This preview has never changed Windows settings.',
        body: `<div class="preview-callout">${icon('info')}<span>Undo clears the latest preview-run record and returns the selected profile to Safe. There are no system changes to reverse.</span></div>`,
        confirmText: 'Undo preview run',
        confirmClass: 'button-danger',
        onConfirm: () => {
          state.profile = 'Safe';
          state.lastRun = null;
          state.activity.unshift({ title: 'Preview history reset', detail: 'Returned to Safe profile · no system changes', time: 'Just now', icon: 'rotate' });
          renderPage();
          showToast('Preview run reset. No Windows changes existed to undo.');
        },
      });
      break;
    case 'export-settings': exportPreviewSettings(); break;
    case 'backup-settings':
      showModal({
        title: 'Back up preview settings?',
        description: 'This saves a JSON file containing preview preferences only.',
        body: `<p>The JSON includes selected profile, local UI toggles, and the sample startup-table state. It does not contain Windows registry values, a restore point, files, HWID, or real device readings.</p>`,
        confirmText: 'Download JSON backup',
        confirmClass: 'button-secondary',
        onConfirm: exportPreviewSettings,
      });
      break;
    case 'check-updates': showToast('No update service is connected in this preview.'); break;
    case 'minecraft-rescan': showGenericReview('Recheck Minecraft launchers', 'Web browsers cannot enumerate installed apps, launcher folders, Java runtimes, or running processes. A native app should ask permission before scanning.', 'Got it'); break;
    case 'copy-jvm': {
      const args = $(`#jvmArgs`)?.textContent || '';
      if (navigator.clipboard?.writeText) navigator.clipboard.writeText(args).then(() => showToast('JVM sample arguments copied.')).catch(() => showToast('Clipboard permission unavailable; select the sample text manually.', 'error'));
      else showToast('Select the sample JVM text and copy it manually.', 'error');
      break;
    }
    default: break;
  }
}

function closeMobileMenu() {
  $('#sidebar')?.classList.remove('open');
  $('#sidebarBackdrop')?.remove();
}

document.addEventListener('click', (event) => {
  const nav = event.target.closest('[data-nav]');
  if (nav) {
    event.preventDefault();
    navigate(nav.dataset.nav);
    return;
  }

  if (event.target.classList.contains('modal-backdrop')) {
    closeModal();
    return;
  }

  const actionButton = event.target.closest('[data-action]');
  if (actionButton) {
    handleAction(actionButton.dataset.action, actionButton);
    return;
  }

  const profile = event.target.closest('[data-profile]');
  if (profile) {
    state.profile = profile.dataset.profile;
    renderPage();
    return;
  }

  const hardwareTab = event.target.closest('[data-hardware-tab]');
  if (hardwareTab) {
    state.hardwareTab = hardwareTab.dataset.hardwareTab;
    renderPage();
    return;
  }

  const dns = event.target.closest('[data-dns]');
  if (dns) {
    state.dnsProfile = dns.dataset.dns;
    renderPage();
    return;
  }

  const serviceFilter = event.target.closest('[data-service-filter]');
  if (serviceFilter) {
    state.serviceFilter = serviceFilter.dataset.serviceFilter;
    renderPage();
    return;
  }

  const serviceReview = event.target.closest('[data-service-review]');
  if (serviceReview) {
    openServiceReview(serviceReview.dataset.serviceReview);
    return;
  }

  const serviceToggle = event.target.closest('[data-service-toggle]');
  if (serviceToggle) {
    handleAction('service-toggle', serviceToggle);
    return;
  }

  const startupToggle = event.target.closest('[data-startup-toggle]');
  if (startupToggle) {
    handleAction('startup-toggle', startupToggle);
    return;
  }

  const appOpen = event.target.closest('[data-app-open]');
  if (appOpen) {
    handleAction('app-open', appOpen);
    return;
  }

  const repair = event.target.closest('[data-repair]');
  if (repair) {
    handleAction('repair', repair);
    return;
  }

  const appSearch = event.target.closest('[data-app-search]');
  if (appSearch) {
    handleAction('app-search', appSearch);
    return;
  }

  const debloat = event.target.closest('[data-debloat-review]');
  if (debloat) {
    openDebloatReview(debloat.dataset.debloatReview);
    return;
  }

  const jvmPreset = event.target.closest('[data-jvm-preset]');
  if (jvmPreset) {
    state.jvmPreset = jvmPreset.dataset.jvmPreset;
    renderPage();
    return;
  }

  const mcProfile = event.target.closest('[data-minecraft-profile]');
  if (mcProfile) {
    state.minecraftProfile = mcProfile.dataset.minecraftProfile;
    renderPage();
    showToast(`${state.minecraftProfile} recommendation selected in preview.`);
  }
});

document.addEventListener('change', (event) => {
  const target = event.target;
  if (target.matches('[data-cleaner-toggle]')) {
    state.cleanerSelection[target.dataset.cleanerToggle] = target.checked;
    renderPage();
    return;
  }
  if (target.matches('[data-gaming-toggle]')) {
    state.gaming[target.dataset.gamingToggle] = target.checked;
    renderPage();
    showToast('Gaming setting updated in preview only.');
    return;
  }
  if (target.matches('[data-privacy-toggle]')) {
    state.privacy[target.dataset.privacyToggle] = target.checked;
    renderPage();
    showToast('Privacy sample state updated in preview only.');
    return;
  }
  if (target.matches('[data-setting-toggle]')) {
    state.settings[target.dataset.settingToggle] = target.checked;
    renderPage();
    showToast('Local preview preference updated.');
    return;
  }
  if (target.id === 'dashboardProfile') {
    state.profile = target.value;
    renderPage();
  }
});

document.addEventListener('input', (event) => {
  const target = event.target;
  if (target.matches('[data-startup-search]')) {
    state.startupSearch = target.value;
    const host = $('#startupTableHost');
    if (host) host.innerHTML = startupTableHTML();
    return;
  }
  if (target.matches('[data-ram-slider]')) {
    state.minecraftRam = Number(target.value);
    const output = $('#ramOutput');
    if (output) output.textContent = `${state.minecraftRam} GB`;
    target.style.setProperty('--range-fill', `${((state.minecraftRam - 2) / 8) * 100}%`);
    const args = state.jvmPreset === 'Minimal' ? `-Xms2G -Xmx${state.minecraftRam}G -XX:+UseG1GC` : `-Xms2G -Xmx${state.minecraftRam}G -XX:+UseG1GC -XX:MaxGCPauseMillis=50 -XX:G1ReservePercent=20`;
    const jvmOutput = $('#jvmArgs');
    if (jvmOutput) jvmOutput.textContent = args;
  }
});

document.addEventListener('keydown', (event) => {
  if (event.key === 'Escape') {
    closeModal();
    closeMobileMenu();
  }
});

renderPage();
