/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2012 Soeren Sonnenburg and Sergey Lisitsyn
 * Copyright (C) 1999-2012 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _MULTICLASSMACHINE_H___
#define _MULTICLASSMACHINE_H___

#include <shogun/machine/Machine.h>
#include <shogun/machine/multiclass/RejectionStrategy.h>

namespace shogun
{

class CFeatures;
class CLabels;
class CRejectionStrategy;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
enum EMulticlassStrategy
{
	ONE_VS_REST_STRATEGY,
	ONE_VS_ONE_STRATEGY,
};
#endif

/** @brief experimental abstract generic multiclass machine class */
class CMulticlassMachine : public CMachine
{
	public:
		/** default constructor  */
		CMulticlassMachine();

		/** standard constructor
		 * @param strategy multiclass strategy
		 * @param machine machine
		 * @param labels labels
		 */
		CMulticlassMachine(EMulticlassStrategy strategy, CMachine* machine, CLabels* labels);

		/** destructor */
		virtual ~CMulticlassMachine();

		/** set machine
		 *
		 * @param num index of machine
		 * @param machine machine to set
		 * @return if setting was successful
		 */
		inline bool set_machine(int32_t num, CMachine* machine)
		{
			ASSERT(num<m_machines.vlen && num>=0);
			SG_REF(machine);
			SG_UNREF(m_machines[num]);
			m_machines[num] = machine;
			return true;
		}

		/** get machine
		 *
		 * @param num index of machine to get
		 * @return SVM at number num
		 */
		inline CMachine* get_machine(int32_t num) const
		{
			ASSERT(num<m_machines.vlen && num>=0);
			SG_REF(m_machines[num]);
			return m_machines[num];
		}

		/** get number of machines
		 *
		 * @return number of machines
		 */
		inline int32_t get_num_machines() const
		{
			return m_machines.vlen;
		}

		/** cleanup */
		void cleanup();

		/** classify all examples
		 *
		 * @return resulting labels
		 */
		virtual CLabels* apply();

		/** classify all examples
		 *
		 * @return resulting labels
		 */
		virtual CLabels* apply(CFeatures* features);

		/** classify one example
		 *
		 * @param num number of example to classify
		 * @return resulting classification
		 */
		virtual float64_t apply(int32_t num);

		/** classify one vs rest
		 *
		 * @return resulting labels
		 */
		virtual CLabels* classify_one_vs_rest();

		/** train one vs rest */
		bool train_one_vs_rest();

		/** get the type of multiclass'ness
		 *
		 * @return multiclass type 1 vs one etc
		 */
		inline EMulticlassStrategy get_multiclass_strategy() const 
		{ 
			return m_multiclass_strategy; 
		}

		/** get rejection strategy */
		inline CRejectionStrategy* get_rejection_strategy() const
		{
			return m_rejection_strategy;
		}
		/** set rejection strategy */
		inline void set_rejection_strategy(CRejectionStrategy* rejection_strategy)
		{
			m_rejection_strategy = rejection_strategy;
		}

		/** get name */
		virtual const char* get_name() const 
		{
			return "MulticlassMachine";
		}

	protected:

		/** train machine */
		virtual bool train_machine(CFeatures* data = NULL);

		/** abstract init machine for training method */ 
		virtual bool init_machine_for_train(CFeatures* data) = 0;

		/** abstract init machines for applying method */
		virtual bool init_machines_for_apply(CFeatures* data) = 0;

		/** check whether machine is ready */
		virtual bool is_ready() = 0;

		/** obtain machine from trained one */
		virtual CMachine* get_machine_from_trained(CMachine* machine) = 0;

		/** get num rhs vectors */
		virtual int32_t get_num_rhs_vectors() = 0;

	private:

		/** init parameters */
		void init();

	protected:
		/** type of multiclass strategy */
		EMulticlassStrategy m_multiclass_strategy;

		/** machine */
		CMachine* m_machine;

		/** machines */
		SGVector<CMachine*> m_machines;

		/** rejection strategy */
		CRejectionStrategy* m_rejection_strategy;
};
}
#endif
