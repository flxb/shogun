/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Sergey Lisitsyn
 * Copyright (C) 2012 Sergey Lisitsyn
 */


#include <shogun/classifier/svm/MulticlassLibLinear.h>
#include <shogun/mathematics/Math.h>

using namespace shogun;

bool CMulticlassLibLinear::train_machine(CFeatures* data)
{
	if (data)
		set_features((CDotFeatures*)data);

	int32_t num_vectors = m_features->get_num_vectors();
	int32_t num_classes = labels->get_num_classes();
	
	problem mc_problem;
	mc_problem.l = num_vectors;
	mc_problem.n = m_features->get_dim_feature_space();
	mc_problem.y = SG_MALLOC(int32_t, mc_problem.l);
	for (int32_t i=0; i<num_vectors; i++)
		mc_problem.y[i] = labels->get_int_label(i);

	mc_problem.x = m_features;
	mc_problem.use_bias = true;

	float64_t* w = SG_MALLOC(float64_t, mc_problem.n*num_classes);
	float64_t* C = SG_MALLOC(float64_t, num_vectors);
	for (int32_t i=0; i<num_vectors; i++)
		C[i] = m_C;

	Solver_MCSVM_CS solver(&mc_problem,num_classes,C,m_epsilon,m_max_iter);
	solver.Solve(w);

	m_machines.destroy_vector();
	m_machines = SGVector<CMachine*>(num_classes);
	for (int32_t i=0; i<num_classes; i++)
	{
		CLinearMachine* machine = new CLinearMachine();
		SGVector<float64_t> cw(mc_problem.n);
		for (int32_t j=0; j<mc_problem.n; j++)
			cw[j] = w[j*num_classes+i];
		machine->set_w(cw);

		m_machines[i] = machine;
	}

	SG_FREE(C);
	SG_FREE(w);
	SG_FREE(mc_problem.y);

	return true;
}
