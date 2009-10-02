/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2009 Soeren Sonnenburg
 * Copyright (C) 2009 Fraunhofer Institute FIRST and Max-Planck-Society
 */
#ifndef __MKLREGRESSION_H__
#define __MKLREGRESSION_H__

#include "lib/common.h"
#include "classifier/mkl/MKL.h"

class CMKLRegression : public CMKL
{
	public:
		/** Constructor
		 *
		 * @param s SVM to use as constraint generator in MKL SILP
		 */
		CMKLRegression(CSVM* s=NULL);

		/** Destructor
		 */
		virtual ~CMKLRegression();

		virtual float64_t compute_sum_alpha();

	protected:
		virtual void init_training();

		/** get classifier type
		 *
		 * @return classifier type MKL_REGRESSION
		 */
		virtual inline EClassifierType get_classifier_type() { return CT_MKLREGRESSION; }

		/** compute mkl dual objective
		 *
		 * @return computed dual objective
		 */
		virtual float64_t compute_mkl_dual_objective();
};
#endif //__MKLREGRESSION_H__