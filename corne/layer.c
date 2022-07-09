// Handles layer-related functionality.

bool entering_layer(
    uint8_t layer, layer_state_t old_layer_state,
    layer_state_t new_layer_state) {
  return get_highest_layer(old_layer_state) != layer &&
    get_highest_layer(new_layer_state) == layer;
}

bool leaving_layer(
    uint8_t layer, layer_state_t old_layer_state,
    layer_state_t new_layer_state) {
  return get_highest_layer(old_layer_state) == layer &&
    get_highest_layer(new_layer_state) != layer;
}
