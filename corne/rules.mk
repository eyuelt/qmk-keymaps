# Note: This is a Makefile. To log, use $(warning 'hello world').

# Note: MAKEFILE_LIST changes whenever an include happens, so this must be
# computed before any includes.
_path_to_this_file = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
_conditional_dir = $(abspath $(dir $(_path_to_this_file))/conditional)


# Enable mouse keys
MOUSEKEY_ENABLE = yes

# Link-time optimization. Reduces binary size but increases compile time.
LTO_ENABLE = yes

# Only one of these can be enabled at a time.
RGB_MATRIX_ENABLE = yes  # Enable RGB matrix.
RGBLIGHT_ENABLE = no     # Disable WS2812 RGB underlight.

# Allow for custom RGB effects.
RGB_MATRIX_CUSTOM_USER = yes


# Enable/disable debug mode depending on flags provided to the build script.
include $(_conditional_dir)/debug/rules.mk
