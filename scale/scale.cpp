#include "scale.h"

#include "scene/main/viewport.h"

void Scale::resize_scale() {
  Vector2 size = Vector2(0, 0);
  Control *control = Object::cast_to<Control>(get_parent());
  if (control) {
	  size = control->get_size();
  } else if (get_viewport()) {
    Viewport *viewport = get_viewport();
    if (viewport->is_size_override_enabled()) {
			size = viewport->get_size_override();
    } else {
			size = viewport->get_size();
    }
  }

  set_position((relative_pos * size) + offset_pos);
  set_size((relative_size * size) + offset_size);
}

void Scale::set_relative_size(const Vector2 &p_relative_size) {
  if (relative_size == p_relative_size) {
    return;
  }
  relative_size = p_relative_size;
  resize_scale();
}

Vector2 Scale::get_relative_size() const {
  return relative_size;
}

void Scale::set_offset_size(const Vector2 &p_offset_size) {
  if (offset_size == p_offset_size) {
    return;
  }
  offset_size = p_offset_size;
  resize_scale();
}
Vector2 Scale::get_offset_size() const {
  return offset_size;
}

void Scale::set_relative_pos(const Vector2 &p_relative_pos) {
  if (relative_pos == p_relative_pos) {
    return;
  }
  relative_pos = p_relative_pos;
  resize_scale();
}
Vector2 Scale::get_relative_pos() const {
  return relative_pos;
}

void Scale::set_offset_pos(const Vector2 &p_offset_pos) {
  if (offset_pos == p_offset_pos) {
    return;
  }
  offset_pos = p_offset_pos;
  resize_scale();
}
Vector2 Scale::get_offset_pos() const {
  return offset_pos;
}

void Scale::_notification(int p_notification) {
  switch (p_notification) {
    case NOTIFICATION_ENTER_TREE: {
      Control *control = Object::cast_to<Control>(get_parent());
      Viewport *viewport = get_viewport();

      if (!viewport->is_connected("size_changed", this, "resize_scale")) {
        viewport->connect("size_changed", this, "resize_scale");
      }
      if (control && !control->is_connected("resized", this, "resize_scale")) {
        control->connect("resized", this, "resize_scale");
      }
      if (!is_connected("item_rect_changed", this, "resize_scale")) {
        connect("item_rect_changed", this, "resize_scale");
      }

    } break;
    case NOTIFICATION_READY: {
      resize_scale();
    } break;
  }
}

void Scale::_bind_methods() {
	ClassDB::bind_method(D_METHOD("resize_scale"), &Scale::resize_scale);
  
	ClassDB::bind_method(D_METHOD("set_relative_size", "relative_size"), &Scale::set_relative_size);
	ClassDB::bind_method(D_METHOD("get_relative_size"), &Scale::get_relative_size);

	ClassDB::bind_method(D_METHOD("set_offset_size", "offset_size"), &Scale::set_offset_size);
	ClassDB::bind_method(D_METHOD("get_offset_size"), &Scale::get_offset_size);

	ClassDB::bind_method(D_METHOD("set_relative_pos", "relative_pos"), &Scale::set_relative_pos);
	ClassDB::bind_method(D_METHOD("get_relative_pos"), &Scale::get_relative_pos);

	ClassDB::bind_method(D_METHOD("set_offset_pos", "offset_pos"), &Scale::set_offset_pos);
	ClassDB::bind_method(D_METHOD("get_offset_pos"), &Scale::get_offset_pos);

  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "relative_size"), "set_relative_size", "get_relative_size");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset_size"), "set_offset_size", "get_offset_size");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "relative_pos"), "set_relative_pos", "get_relative_pos");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset_pos"), "set_offset_pos", "get_offset_pos");
}

Scale::Scale() {
  relative_size = Vector2(0, 0);
  offset_size = Vector2(40, 40);
  relative_pos = Vector2(0, 0);
  offset_pos = Vector2(0, 0);
}

Scale::~Scale() {
}
