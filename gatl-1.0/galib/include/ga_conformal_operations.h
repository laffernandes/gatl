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
 * Set of products/operations to be used within the conformal geometric algebra model.
 * The using directive allows an individual name from a specific namespace (e.g., ga::conformal
 * namespace) to be used without explicit qualification inside the current namespace.
 *******************************************************************************************************/

using ga::conformal::flat_direction;		// Direction parameter of a flat.
using ga::conformal::flat_location;			// Location parameter of a flat.
using ga::conformal::round_direction;		// Direction parameter of a round.
using ga::conformal::round_location;		// Location parameter of a round.
using ga::conformal::round_size2;			// Squared size parameter of a round.
using ga::conformal::tangent_direction;		// Direction parameter of a tangent.
using ga::conformal::tangent_location;		// Location parameter of a tangent.
using ga::conformal::tangent_size2;			// Squared size parameter of a tangent.

using ga::conformal::is_direction;			// Direction test.
using ga::conformal::is_dual_direction;		// Dual direction test.
using ga::conformal::is_dual_flat;			// Dual flat test.
using ga::conformal::is_dual_round;			// Dual round test.
using ga::conformal::is_dual_tangent;		// Dual tangent test.
using ga::conformal::is_flat;				// Flat test.
using ga::conformal::is_round;				// Round test.
using ga::conformal::is_tangent;			// Tangent test.

using ga::conformal::point;					// Point from coordinates.
using ga::conformal::vector;				// Vector from coordinates.
