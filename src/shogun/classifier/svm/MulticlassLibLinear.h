/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Sergey Lisitsyn
 * Copyright (C) 2012 Sergey Lisitsyn
 */

#ifndef _MULTICLASSLIBLINEAR_H___
#define _MULTICLASSLIBLINEAR_H___

#include <shogun/lib/common.h>
#include <shogun/features/DotFeatures.h>
#include <shogun/classifier/svm/SVM_linear.h>
#include <shogun/machine/multiclass/LinearMulticlassMachine.h>

namespace shogun
{

/** @brief multiclass LibLinear wrapper */
class CMulticlassLibLinear : public CLinearMulticlassMachine
{
	public:
		/** default constructor  */
		CMulticlassLibLinear() : CLinearMulticlassMachine()
		{
		}

		/** standard constructor
		 * @param C C regularication constant value
		 * @param features features 
		 * @param labs labels
		 */
		CMulticlassLibLinear(float64_t C, CDotFeatures* features, CLabels* labs) :
			CLinearMulticlassMachine(ONE_VS_REST_STRATEGY,features,NULL,labs), m_C(C)
		{
			set_epsilon(1e-2);
			set_max_iter(10000);
		}

		/** destructor */
		virtual ~CMulticlassLibLinear()
		{
		}

		/** get name */
		virtual const char* get_name() const 
		{
			return "MulticlassLibLinear";
		}

		/** set C 
		 * @param C C value
		 */
		inline void set_C(int32_t C) 
		{
			ASSERT(C>0);
			m_C = C;
		}
		/** get C
		 * @return C value
		 */
		inline int32_t get_C() const { return m_C; }

		/** set epsilon 
		 * @param epsilon epsilon value
		 */
		inline void set_epsilon(float64_t epsilon) 
		{ 
			ASSERT(epsilon>0);
			m_epsilon = epsilon; 
		}
		/** get epsilon
		 * @return epsilon value
		 */
		inline float64_t get_epsilon() const { return m_epsilon; }

		/** set max iter
		 * @param max_iter max iter value
		 */
		inline void set_max_iter(int32_t max_iter) 
		{
			ASSERT(max_iter>0);
			m_max_iter = max_iter;
		}
		/** get max iter
		 * @return max iter value
		 */
		inline int32_t get_max_iter() const { return m_max_iter; }


protected:

		/** train machine */
		virtual bool train_machine(CFeatures* data = NULL);

protected:

		/** regularization constant for each machine */
		float64_t m_C;

		/** tolerance */
		float64_t m_epsilon;

		/** max number of iterations */
		int32_t m_max_iter;
};
}
#endif
