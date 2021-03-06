/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2007-2009 Soeren Sonnenburg
 * Copyright (C) 2007-2009 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include <shogun/lib/common.h>
#include <shogun/io/SGIO.h>
#include <shogun/distance/SparseEuclidianDistance.h>
#include <shogun/features/Features.h>
#include <shogun/features/SparseFeatures.h>

using namespace shogun;

CSparseEuclidianDistance::CSparseEuclidianDistance()
: CSparseDistance<float64_t>()
{
	init();
}

CSparseEuclidianDistance::CSparseEuclidianDistance(
	CSparseFeatures<float64_t>* l, CSparseFeatures<float64_t>* r)
: CSparseDistance<float64_t>()
{
	init();
	init(l, r);
}

CSparseEuclidianDistance::~CSparseEuclidianDistance()
{
	cleanup();
}

bool CSparseEuclidianDistance::init(CFeatures* l, CFeatures* r)
{
	CSparseDistance<float64_t>::init(l, r);

	cleanup();

	sq_lhs=SG_MALLOC(float64_t, lhs->get_num_vectors());
	sq_lhs=((CSparseFeatures<float64_t>*) lhs)->compute_squared(sq_lhs);

	if (lhs==rhs)
		sq_rhs=sq_lhs;
	else
	{
		sq_rhs=SG_MALLOC(float64_t, rhs->get_num_vectors());
		sq_rhs=((CSparseFeatures<float64_t>*) rhs)->compute_squared(sq_rhs);
	}

	return true;
}

void CSparseEuclidianDistance::cleanup()
{
	if (sq_lhs != sq_rhs)
		SG_FREE(sq_rhs);
	sq_rhs = NULL;

	SG_FREE(sq_lhs);
	sq_lhs = NULL;
}

float64_t CSparseEuclidianDistance::compute(int32_t idx_a, int32_t idx_b)
{
	float64_t result=((CSparseFeatures<float64_t>*) lhs)->compute_squared_norm(
		(CSparseFeatures<float64_t>*) lhs, sq_lhs, idx_a,
		(CSparseFeatures<float64_t>*) rhs, sq_rhs, idx_b);

	return CMath::sqrt(result);
}

void CSparseEuclidianDistance::init()
{
	sq_lhs=NULL;
	sq_rhs=NULL;
}
