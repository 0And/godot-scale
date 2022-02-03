
#ifndef SCALE_H
#define SCALE_H

#include "scene/gui/control.h"

class Scale : public Control {
	GDCLASS(Scale, Control);
	
	public:
		enum RelativeConstraint {
			RELATIVE_XY,
			RELATIVE_XX,
			RELATIVE_YY,
			RELATIVE_YX,
		};

	private:
		Vector2 relative_size;
		Vector2 offset_size;
		Vector2 relative_pos;
		Vector2 offset_pos;
		RelativeConstraint relative_constraint;
		
		void resize_scale();

	protected:
		void _notification(int p_notification);

		static void _bind_methods();

		//bind helpers
	public:

		void set_relative_size(const Vector2 &p_relative_size);
		Vector2 get_relative_size() const;

		void set_offset_size(const Vector2 &p_offset_size);
		Vector2 get_offset_size() const;

		void set_relative_pos(const Vector2 &p_relative_pos);
		Vector2 get_relative_pos() const;
		
		void set_offset_pos(const Vector2 &p_offset_pos);
		Vector2 get_offset_pos() const;

		void set_relative_constraint(RelativeConstraint p_relative_constraint);
		RelativeConstraint get_relative_constraint() const;
		
		Scale();
		~Scale();

};

VARIANT_ENUM_CAST(Scale::RelativeConstraint);

#endif // SCALE_H
