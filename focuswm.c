#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <stdlib.h>

#define stk(s)      XKeysymToKeycode(d, XStringToKeysym(s))
#define on(ev, x)   if (e.type == ev) { x; }
#define keys(k, _)  XGrabKey(d, stk(k), Mod1Mask, r, 1, 1, 1);
#define map(k, x)   if (e.xkey.keycode == stk(k)) { x; }

#define TBL(x)  x("u", XCirculateSubwindowsUp(d, r); XSetInputFocus(d, e.xkey.window, 2, 0)) \
                x("f", system("st -e lf &")) \
                x("e", system("thunar &")) \
                x("b", system("vivaldi &")) \
                x("semicolon", system("st &")) \
                x("apostrophe", XKillClient(d, e.xkey.subwindow)) \
                x("bracketleft", system("redshift -O 3500")) \
                x("bracketright", system("redshift -x")) \
                x("comma", system("nmcli radio wifi on")) \
                x("period", system("nmcli radio wifi off")) \
                x("m", system("~/dotfiles/.config/rofi/scripts/all.sh")) \
                x("p", system("~/dotfiles/.config/rofi/scripts/power/system/powermenu.sh")) \
                x("d", system("rofi -show run -config ~/dotfiles/.config/rofi/themes/cmd/cmd.rasi")) \
                x("k", system("~/dotfiles/.config/rofi/scripts/keybindings/focuswm-bindings/focuswm-bindings.sh"))

int main() {
    Display *d = XOpenDisplay(0); 
    Window r = DefaultRootWindow(d);
    int sw = DisplayWidth(d, DefaultScreen(d));
    int sh = DisplayHeight(d, DefaultScreen(d));
    XEvent e;
    
    // Multi-monitor support with Xinerama
    int num_monitors = 0;
    XineramaScreenInfo *monitors = XineramaQueryScreens(d, &num_monitors);
    int current_monitor = 0;
    
    system("feh --bg-scale ~/dotfiles/.local/share/wallpapers/AtumOS-Wallpapers/1.png");
    
    XSelectInput(d, r, SubstructureRedirectMask);
    TBL(keys);
    XGrabKey(d, stk("Escape"), Mod1Mask, r, 1, 1, 1);
    XGrabKey(d, stk("bracketleft"), Mod4Mask, r, 1, 1, 1);
    XGrabKey(d, stk("bracketright"), Mod4Mask, r, 1, 1, 1);
    XGrabKey(d, stk("t"), Mod1Mask | ShiftMask, r, 1, 1, 1);
    XGrabKey(d, stk("b"), Mod1Mask | ShiftMask, r, 1, 1, 1);
    XGrabKey(d, stk("i"), Mod1Mask, r, 1, 1, 1); // Alt+i
    XGrabKey(d, stk("o"), Mod1Mask, r, 1, 1, 1); // Alt+o

    while (!XNextEvent(d, &e)) {
        on(ConfigureRequest, XMoveResizeWindow(d, e.xconfigurerequest.window, 
                                                monitors ? monitors[current_monitor].x_org : 0,
                                                monitors ? monitors[current_monitor].y_org : 0,
                                                monitors ? monitors[current_monitor].width : sw,
                                                monitors ? monitors[current_monitor].height : sh))
        on(MapRequest, XMapWindow(d, e.xmaprequest.window);
                       XMoveResizeWindow(d, e.xmaprequest.window,
                                         monitors ? monitors[current_monitor].x_org : 0,
                                         monitors ? monitors[current_monitor].y_org : 0,
                                         monitors ? monitors[current_monitor].width : sw,
                                         monitors ? monitors[current_monitor].height : sh);
                       XSetInputFocus(d, e.xmaprequest.window, 2, 0))
        on(KeyPress, if (e.xkey.keycode == stk("Escape")) { 
                         if (monitors) XFree(monitors);
                         XCloseDisplay(d); 
                         exit(0); 
                     }
                     // Alt+i: Switch to next monitor
                     if (e.xkey.keycode == stk("i") && num_monitors > 1) {
                         current_monitor = (current_monitor + 1) % num_monitors;
                         XWarpPointer(d, None, r, 0, 0, 0, 0,
                                     monitors[current_monitor].x_org + monitors[current_monitor].width / 2,
                                     monitors[current_monitor].y_org + monitors[current_monitor].height / 2);
                     }
                     // Alt+o: Send current window to next monitor
                     if (e.xkey.keycode == stk("o") && num_monitors > 1) {
                         Window focused;
                         int revert;
                         XGetInputFocus(d, &focused, &revert);
                         if (focused && focused != r) {
                             int next_mon = (current_monitor + 1) % num_monitors;
                             XMoveResizeWindow(d, focused,
                                             monitors[next_mon].x_org,
                                             monitors[next_mon].y_org,
                                             monitors[next_mon].width,
                                             monitors[next_mon].height);
                         }
                     }
                     if (e.xkey.state & Mod4Mask) {
                         if (e.xkey.keycode == stk("bracketleft")) { system("brightnessctl set 10%-"); }
                         if (e.xkey.keycode == stk("bracketright")) { system("brightnessctl set 10%+"); }
                     } else if (e.xkey.keycode == stk("t") && (e.xkey.state & ShiftMask)) {
                         system("~/dotfiles/.config/hypr/scripts/date-time.sh");
                     } else if (e.xkey.keycode == stk("b") && (e.xkey.state & ShiftMask)) {
                         system("librewolf &");
                     } else {
                         TBL(map)
                     })
    }
}
