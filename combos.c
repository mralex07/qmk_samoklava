// Home row mod tap keys
#define HM_A SFT_T(KC_A)
#define HM_S ALT_T(KC_S)
#define HM_D CTL_T(KC_D)
#define HM_F GUI_T(KC_F)
#define HM_J GUI_T(KC_J)
#define HM_K CTL_T(KC_K)
#define HM_L ALT_T(KC_L)
#define HM_SCLN SFT_T(KC_SCLN)

COMB(KC_VOLU,	KC_VOLU, KC_Y, KC_U)
COMB(KC_VOLD, 	KC_VOLD, KC_H, HM_J)
COMB(KC_MUTE, 	KC_MUTE, KC_N, M_TH)
COMB(KC_BSPC, 	KC_BSPC, KC_O, KC_P)

SUBS(vi_quit,	":q!", KC_Q, KC_W)
SUBS(vi_save,	":wq!", KC_Z, KC_X)