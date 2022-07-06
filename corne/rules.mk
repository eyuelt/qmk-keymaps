# Note: This is a Makefile. To log, use $(warning 'hello world').

# Note: MAKEFILE_LIST changes whenever an include happens, so this must be
# computed before any includes.
_path_to_this_file = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
_conditional_dir = $(abspath $(dir $(_path_to_this_file))/conditional)

MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = no     # Disable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes
LTO_ENABLE      = yes    # Link-time optimization. Reduces binary size.

# enable debug mode depending on flags provided to build script
include $(_conditional_dir)/debug/rules.mk
