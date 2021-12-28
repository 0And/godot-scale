tool
extends Control

export(Vector2) var relative_size = Vector2(0, 0) setget set_relative_size
export(Vector2) var offset_size = Vector2(40, 40) setget set_offset_size
export(Vector2) var relative_position = Vector2(0, 0) setget set_relative_pos
export(Vector2) var offset_position = Vector2(0, 0) setget set_offset_pos
func set_relative_size(vec):
	relative_size = vec
	resize()
func set_offset_size(vec):
	offset_size = vec
	resize()
func set_relative_pos(vec):
	relative_position = vec
	resize()
func set_offset_pos(vec):
	offset_position = vec
	resize()

func resize():
	var size = Vector2()
	if get_parent() is Control:
		size = get_parent().rect_size
	elif get_viewport():
		if get_viewport().is_size_override_enabled():
			size = get_viewport().get_size_override()
		else:
			size = get_viewport().size
	rect_position = (relative_position * size) + offset_position
	rect_size = (relative_size * size) + offset_size

func _enter_tree():
	if not get_viewport().is_connected("size_changed", self, "resize"):
		get_viewport().connect("size_changed", self, "resize")
	if get_parent() is Control and not get_parent().is_connected("resized", self, "resize"):
		get_parent().connect("resized", self, "resize")
	if not is_connected("item_rect_changed", self, "resize"):
		connect("item_rect_changed", self, "resize")

func _ready():
	resize()