/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

/*******************************************************************************************************
 * Set of products/operations to be used within the homogeneous geometric algebra model.
 * The using directive allows an individual name from a specific namespace (e.g., ga::homogeneous
 * namespace) to be used without explicit qualification inside the current namespace.
 *******************************************************************************************************/

using ga::homogeneous::flat_direction;			// Direction parameter of a k-flat.
using ga::homogeneous::flat_moment;				// Moment parameter of a k-flat.
using ga::homogeneous::flat_support_vector;		// Support vector parameter of a k-flat.
using ga::homogeneous::flat_unit_support_point;	// Unit support point parameter of a k-flat.

using ga::homogeneous::is_direction;			// Direction (improper flat) test.
using ga::homogeneous::is_flat;					// Flat test.
using ga::homogeneous::is_improper_flat;		// Improper flat test.
using ga::homogeneous::is_proper_flat;			// Proper flat test.

using ga::homogeneous::translate;				// Translation.

using ga::homogeneous::point;					// Point from coordinates.
using ga::homogeneous::vector;					// Vector (improper point) from coordinates.
