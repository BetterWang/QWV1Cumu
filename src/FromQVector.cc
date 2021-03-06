/**
 * @file   correlations/closed/FromQVector.hh
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Oct 24 23:45:40 2013
 *
 * @brief  Cumulant using closed-form expressions
 */
/*
 * Multi-particle correlations
 * Copyright (C) 2013 K.Gulbrandsen, A.Bilandzic, C.H. Christensen.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses.
 */

#include <correlations/closed/FromQVector.hh>
namespace correlations {
  /**
   * Namespace for closed form calculations
   */
  namespace closed {
      /**
       * Do the 5-particle calculation
       *
       * @param n1 1st Harmonic
       * @param n2 2nd Harmonic
       * @param n3 3rd Harmonic
       * @param n4 4th Harmonic
       * @param n5 5th Harmonic
       *
       * @return The correlator
       */
      Complex FromQVector::uc5(const Harmonic n1,
		  const Harmonic n2,
		  const Harmonic n3,
		  const Harmonic n4,
		  const Harmonic n5) const
      {
	const Real k2  = 2;
	const Real k6  = 6;
	const Real k24 = 24;
	return (_q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n5,1)
		-_q(n1+n2,2)*_q(n3,1)*_q(n4,1)*_q(n5,1)
		-_q(n2,1)*_q(n1+n3,2)*_q(n4,1)*_q(n5,1)
		-_q(n1,1)*_q(n2+n3,2)*_q(n4,1)*_q(n5,1)
		+ k2*_q(n1+n2+n3,3)*_q(n4,1)*_q(n5,1)
		-_q(n2,1)*_q(n3,1)*_q(n1+n4,2)*_q(n5,1)
		+ _q(n2+n3,2)*_q(n1+n4,2)*_q(n5,1)
		-_q(n1,1)*_q(n3,1)*_q(n2+n4,2)*_q(n5,1)
		+ _q(n1+n3,2)*_q(n2+n4,2)*_q(n5,1)
		+k2*_q(n3,1)*_q(n1+n2+n4,3)*_q(n5,1)
		-_q(n1,1)*_q(n2,1)*_q(n3+n4,2)*_q(n5,1)
		+_q(n1+n2,2)*_q(n3+n4,2)*_q(n5,1)
		+ k2*_q(n2,1)*_q(n1+n3+n4,3)*_q(n5,1)
		+k2*_q(n1,1)*_q(n2+n3+n4,3)*_q(n5,1)
		-k6*_q(n1+n2+n3+n4,4)*_q(n5,1)
		-_q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n1+n5,2)
		+ _q(n2+n3,2)*_q(n4,1)*_q(n1+n5,2)
		+_q(n3,1)*_q(n2+n4,2)*_q(n1+n5,2)
		+ _q(n2,1)*_q(n3+n4,2)*_q(n1+n5,2)
		-k2*_q(n2+n3+n4,3)*_q(n1+n5,2)
		-_q(n1,1)*_q(n3,1)*_q(n4,1)*_q(n2+n5,2)
		+_q(n1+n3,2)*_q(n4,1)*_q(n2+n5,2)
		+ _q(n3,1)*_q(n1+n4,2)*_q(n2+n5,2)
		+_q(n1,1)*_q(n3+n4,2)*_q(n2+n5,2)
		-k2*_q(n1+n3+n4,3)*_q(n2+n5,2)
		+k2*_q(n3,1)*_q(n4,1)*_q(n1+n2+n5,3)
		-k2*_q(n3+n4,2)*_q(n1+n2+n5,3)
		-_q(n1,1)*_q(n2,1)*_q(n4,1)*_q(n3+n5,2)
		+_q(n1+n2,2)*_q(n4,1)*_q(n3+n5,2)
		+_q(n2,1)*_q(n1+n4,2)*_q(n3+n5,2)
		+_q(n1,1)*_q(n2+n4,2)*_q(n3+n5,2)
		-k2*_q(n1+n2+n4,3)*_q(n3+n5,2)
		+k2*_q(n2,1)*_q(n4,1)*_q(n1+n3+n5,3)
		-k2*_q(n2+n4,2)*_q(n1+n3+n5,3)
		+ k2*_q(n1,1)*_q(n4,1)*_q(n2+n3+n5,3)
		-k2*_q(n1+n4,2)*_q(n2+n3+n5,3)
		-k6*_q(n4,1)*_q(n1+n2+n3+n5,4)
		-_q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n4+n5,2)
		+ _q(n1+n2,2)*_q(n3,1)*_q(n4+n5,2)
		+_q(n2,1)*_q(n1+n3,2)*_q(n4+n5,2)
		+ _q(n1,1)*_q(n2+n3,2)*_q(n4+n5,2)
		-k2*_q(n1+n2+n3,3)*_q(n4+n5,2)
		+k2*_q(n2,1)*_q(n3,1)*_q(n1+n4+n5,3)
		-k2*_q(n2+n3,2)*_q(n1+n4+n5,3)
		+k2*_q(n1,1)*_q(n3,1)*_q(n2+n4+n5,3)
		-k2*_q(n1+n3,2)*_q(n2+n4+n5,3)
		-k6*_q(n3,1)*_q(n1+n2+n4+n5,4)
		+k2*_q(n1,1)*_q(n2,1)*_q(n3+n4+n5,3)
		-k2*_q(n1+n2,2)*_q(n3+n4+n5,3)
		-k6*_q(n2,1)*_q(n1+n3+n4+n5,4)
		-k6*_q(n1,1)*_q(n2+n3+n4+n5,4)
		+k24*_q(n1+n2+n3+n4+n5,5));
      }
      /**
       * Do the 6-particle calculation
       *
       * @param n1 1st Harmonic
       * @param n2 2nd Harmonic
       * @param n3 3rd Harmonic
       * @param n4 4th Harmonic
       * @param n5 5th Harmonic
       * @param n6 6th Harmonic
       *
       * @return The correlator
       */
      Complex FromQVector::uc6(const Harmonic n1,
			  const Harmonic n2,
			  const Harmonic n3,
			  const Harmonic n4,
			  const Harmonic n5,
			  const Harmonic n6) const
      {
	const Real k2   = 2;
	const Real k6   = 6;
	const Real k24  = 24;
	const Real k120 = 120;
	return (_q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n5,1)*_q(n6,1)
		- _q(n1+n2,2)*_q(n3,1)*_q(n4,1)*_q(n5,1)*_q(n6,1)
		- _q(n2,1)*_q(n1+n3,2)*_q(n4,1)*_q(n5,1)*_q(n6,1)
		- _q(n1,1)*_q(n2+n3,2)*_q(n4,1)*_q(n5,1)*_q(n6,1)
		+ k2*_q(n1+n2+n3,3)*_q(n4,1)*_q(n5,1)*_q(n6,1)
		- _q(n2,1)*_q(n3,1)*_q(n1+n4,2)*_q(n5,1)*_q(n6,1)
		+ _q(n2+n3,2)*_q(n1+n4,2)*_q(n5,1)*_q(n6,1)
		- _q(n1,1)*_q(n3,1)*_q(n2+n4,2)*_q(n5,1)*_q(n6,1)
		+ _q(n1+n3,2)*_q(n2+n4,2)*_q(n5,1)*_q(n6,1)
		+ k2*_q(n3,1)*_q(n1+n2+n4,3)*_q(n5,1)*_q(n6,1)
		- _q(n1,1)*_q(n2,1)*_q(n3+n4,2)*_q(n5,1)*_q(n6,1)
		+ _q(n1+n2,2)*_q(n3+n4,2)*_q(n5,1)*_q(n6,1)
		+ k2*_q(n2,1)*_q(n1+n3+n4,3)*_q(n5,1)*_q(n6,1)
		+ k2*_q(n1,1)*_q(n2+n3+n4,3)*_q(n5,1)*_q(n6,1)
		- k6*_q(n1+n2+n3+n4,4)*_q(n5,1)*_q(n6,1)
		- _q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n1+n5,2)*_q(n6,1)
		+ _q(n2+n3,2)*_q(n4,1)*_q(n1+n5,2)*_q(n6,1)
		+ _q(n3,1)*_q(n2+n4,2)*_q(n1+n5,2)*_q(n6,1)
		+ _q(n2,1)*_q(n3+n4,2)*_q(n1+n5,2)*_q(n6,1)
		- k2*_q(n2+n3+n4,3)*_q(n1+n5,2)*_q(n6,1)
		- _q(n1,1)*_q(n3,1)*_q(n4,1)*_q(n2+n5,2)*_q(n6,1)
		+ _q(n1+n3,2)*_q(n4,1)*_q(n2+n5,2)*_q(n6,1)
		+ _q(n3,1)*_q(n1+n4,2)*_q(n2+n5,2)*_q(n6,1)
		+ _q(n1,1)*_q(n3+n4,2)*_q(n2+n5,2)*_q(n6,1)
		- k2*_q(n1+n3+n4,3)*_q(n2+n5,2)*_q(n6,1)
		+ k2*_q(n3,1)*_q(n4,1)*_q(n1+n2+n5,3)*_q(n6,1)
		- k2*_q(n3+n4,2)*_q(n1+n2+n5,3)*_q(n6,1)
		- _q(n1,1)*_q(n2,1)*_q(n4,1)*_q(n3+n5,2)*_q(n6,1)
		+ _q(n1+n2,2)*_q(n4,1)*_q(n3+n5,2)*_q(n6,1)
		+ _q(n2,1)*_q(n1+n4,2)*_q(n3+n5,2)*_q(n6,1)
		+ _q(n1,1)*_q(n2+n4,2)*_q(n3+n5,2)*_q(n6,1)
		- k2*_q(n1+n2+n4,3)*_q(n3+n5,2)*_q(n6,1)
		+ k2*_q(n2,1)*_q(n4,1)*_q(n1+n3+n5,3)*_q(n6,1)
		- k2*_q(n2+n4,2)*_q(n1+n3+n5,3)*_q(n6,1)
		+ k2*_q(n1,1)*_q(n4,1)*_q(n2+n3+n5,3)*_q(n6,1)
		- k2*_q(n1+n4,2)*_q(n2+n3+n5,3)*_q(n6,1)
		- k6*_q(n4,1)*_q(n1+n2+n3+n5,4)*_q(n6,1)
		- _q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n4+n5,2)*_q(n6,1)
		+ _q(n1+n2,2)*_q(n3,1)*_q(n4+n5,2)*_q(n6,1)
		+ _q(n2,1)*_q(n1+n3,2)*_q(n4+n5,2)*_q(n6,1)
		+ _q(n1,1)*_q(n2+n3,2)*_q(n4+n5,2)*_q(n6,1)
		- k2*_q(n1+n2+n3,3)*_q(n4+n5,2)*_q(n6,1)
		+ k2*_q(n2,1)*_q(n3,1)*_q(n1+n4+n5,3)*_q(n6,1)
		- k2*_q(n2+n3,2)*_q(n1+n4+n5,3)*_q(n6,1)
		+ k2*_q(n1,1)*_q(n3,1)*_q(n2+n4+n5,3)*_q(n6,1)
		- k2*_q(n1+n3,2)*_q(n2+n4+n5,3)*_q(n6,1)
		- k6*_q(n3,1)*_q(n1+n2+n4+n5,4)*_q(n6,1)
		+ k2*_q(n1,1)*_q(n2,1)*_q(n3+n4+n5,3)*_q(n6,1)
		- k2*_q(n1+n2,2)*_q(n3+n4+n5,3)*_q(n6,1)
		- k6*_q(n2,1)*_q(n1+n3+n4+n5,4)*_q(n6,1)
		- k6*_q(n1,1)*_q(n2+n3+n4+n5,4)*_q(n6,1)
		+ k24*_q(n1+n2+n3+n4+n5,5)*_q(n6,1)
		- _q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n5,1)*_q(n1+n6,2)
		+ _q(n2+n3,2)*_q(n4,1)*_q(n5,1)*_q(n1+n6,2)
		+ _q(n3,1)*_q(n2+n4,2)*_q(n5,1)*_q(n1+n6,2)
		+ _q(n2,1)*_q(n3+n4,2)*_q(n5,1)*_q(n1+n6,2)
		- k2*_q(n2+n3+n4,3)*_q(n5,1)*_q(n1+n6,2)
		+ _q(n3,1)*_q(n4,1)*_q(n2+n5,2)*_q(n1+n6,2)
		- _q(n3+n4,2)*_q(n2+n5,2)*_q(n1+n6,2)
		+ _q(n2,1)*_q(n4,1)*_q(n3+n5,2)*_q(n1+n6,2)
		- _q(n2+n4,2)*_q(n3+n5,2)*_q(n1+n6,2)
		- k2*_q(n4,1)*_q(n2+n3+n5,3)*_q(n1+n6,2)
		+ _q(n2,1)*_q(n3,1)*_q(n4+n5,2)*_q(n1+n6,2)
		- _q(n2+n3,2)*_q(n4+n5,2)*_q(n1+n6,2)
		- k2*_q(n3,1)*_q(n2+n4+n5,3)*_q(n1+n6,2)
		- k2*_q(n2,1)*_q(n3+n4+n5,3)*_q(n1+n6,2)
		+ k6*_q(n2+n3+n4+n5,4)*_q(n1+n6,2)
		- _q(n1,1)*_q(n3,1)*_q(n4,1)*_q(n5,1)*_q(n2+n6,2)
		+ _q(n1+n3,2)*_q(n4,1)*_q(n5,1)*_q(n2+n6,2)
		+ _q(n3,1)*_q(n1+n4,2)*_q(n5,1)*_q(n2+n6,2)
		+ _q(n1,1)*_q(n3+n4,2)*_q(n5,1)*_q(n2+n6,2)
		- k2*_q(n1+n3+n4,3)*_q(n5,1)*_q(n2+n6,2)
		+ _q(n3,1)*_q(n4,1)*_q(n1+n5,2)*_q(n2+n6,2)
		- _q(n3+n4,2)*_q(n1+n5,2)*_q(n2+n6,2)
		+ _q(n1,1)*_q(n4,1)*_q(n3+n5,2)*_q(n2+n6,2)
		- _q(n1+n4,2)*_q(n3+n5,2)*_q(n2+n6,2)
		- k2*_q(n4,1)*_q(n1+n3+n5,3)*_q(n2+n6,2)
		+ _q(n1,1)*_q(n3,1)*_q(n4+n5,2)*_q(n2+n6,2)
		- _q(n1+n3,2)*_q(n4+n5,2)*_q(n2+n6,2)
		- k2*_q(n3,1)*_q(n1+n4+n5,3)*_q(n2+n6,2)
		- k2*_q(n1,1)*_q(n3+n4+n5,3)*_q(n2+n6,2)
		+ k6*_q(n1+n3+n4+n5,4)*_q(n2+n6,2)
		+ k2*_q(n3,1)*_q(n4,1)*_q(n5,1)*_q(n1+n2+n6,3)
		- k2*_q(n3+n4,2)*_q(n5,1)*_q(n1+n2+n6,3)
		- k2*_q(n4,1)*_q(n3+n5,2)*_q(n1+n2+n6,3)
		- k2*_q(n3,1)*_q(n4+n5,2)*_q(n1+n2+n6,3)
		+ 4.*_q(n3+n4+n5,3)*_q(n1+n2+n6,3)
		- _q(n1,1)*_q(n2,1)*_q(n4,1)*_q(n5,1)*_q(n3+n6,2)
		+ _q(n1+n2,2)*_q(n4,1)*_q(n5,1)*_q(n3+n6,2)
		+ _q(n2,1)*_q(n1+n4,2)*_q(n5,1)*_q(n3+n6,2)
		+ _q(n1,1)*_q(n2+n4,2)*_q(n5,1)*_q(n3+n6,2)
		- k2*_q(n1+n2+n4,3)*_q(n5,1)*_q(n3+n6,2)
		+ _q(n2,1)*_q(n4,1)*_q(n1+n5,2)*_q(n3+n6,2)
		- _q(n2+n4,2)*_q(n1+n5,2)*_q(n3+n6,2)
		+ _q(n1,1)*_q(n4,1)*_q(n2+n5,2)*_q(n3+n6,2)
		- _q(n1+n4,2)*_q(n2+n5,2)*_q(n3+n6,2)
		- k2*_q(n4,1)*_q(n1+n2+n5,3)*_q(n3+n6,2)
		+ _q(n1,1)*_q(n2,1)*_q(n4+n5,2)*_q(n3+n6,2)
		- _q(n1+n2,2)*_q(n4+n5,2)*_q(n3+n6,2)
		- k2*_q(n2,1)*_q(n1+n4+n5,3)*_q(n3+n6,2)
		- k2*_q(n1,1)*_q(n2+n4+n5,3)*_q(n3+n6,2)
		+ k6*_q(n1+n2+n4+n5,4)*_q(n3+n6,2)
		+ k2*_q(n2,1)*_q(n4,1)*_q(n5,1)*_q(n1+n3+n6,3)
		- k2*_q(n2+n4,2)*_q(n5,1)*_q(n1+n3+n6,3)
		- k2*_q(n4,1)*_q(n2+n5,2)*_q(n1+n3+n6,3)
		- k2*_q(n2,1)*_q(n4+n5,2)*_q(n1+n3+n6,3)
		+ 4.*_q(n2+n4+n5,3)*_q(n1+n3+n6,3)
		+ k2*_q(n1,1)*_q(n4,1)*_q(n5,1)*_q(n2+n3+n6,3)
		- k2*_q(n1+n4,2)*_q(n5,1)*_q(n2+n3+n6,3)
		- k2*_q(n4,1)*_q(n1+n5,2)*_q(n2+n3+n6,3)
		- k2*_q(n1,1)*_q(n4+n5,2)*_q(n2+n3+n6,3)
		+ 4.*_q(n1+n4+n5,3)*_q(n2+n3+n6,3)
		- k6*_q(n4,1)*_q(n5,1)*_q(n1+n2+n3+n6,4)
		+ k6*_q(n4+n5,2)*_q(n1+n2+n3+n6,4)
		- _q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n5,1)*_q(n4+n6,2)
		+ _q(n1+n2,2)*_q(n3,1)*_q(n5,1)*_q(n4+n6,2)
		+ _q(n2,1)*_q(n1+n3,2)*_q(n5,1)*_q(n4+n6,2)
		+ _q(n1,1)*_q(n2+n3,2)*_q(n5,1)*_q(n4+n6,2)
		- k2*_q(n1+n2+n3,3)*_q(n5,1)*_q(n4+n6,2)
		+ _q(n2,1)*_q(n3,1)*_q(n1+n5,2)*_q(n4+n6,2)
		- _q(n2+n3,2)*_q(n1+n5,2)*_q(n4+n6,2)
		+ _q(n1,1)*_q(n3,1)*_q(n2+n5,2)*_q(n4+n6,2)
		- _q(n1+n3,2)*_q(n2+n5,2)*_q(n4+n6,2)
		- k2*_q(n3,1)*_q(n1+n2+n5,3)*_q(n4+n6,2)
		+ _q(n1,1)*_q(n2,1)*_q(n3+n5,2)*_q(n4+n6,2)
		- _q(n1+n2,2)*_q(n3+n5,2)*_q(n4+n6,2)
		- k2*_q(n2,1)*_q(n1+n3+n5,3)*_q(n4+n6,2)
		- k2*_q(n1,1)*_q(n2+n3+n5,3)*_q(n4+n6,2)
		+ k6*_q(n1+n2+n3+n5,4)*_q(n4+n6,2)
		+ k2*_q(n2,1)*_q(n3,1)*_q(n5,1)*_q(n1+n4+n6,3)
		- k2*_q(n2+n3,2)*_q(n5,1)*_q(n1+n4+n6,3)
		- k2*_q(n3,1)*_q(n2+n5,2)*_q(n1+n4+n6,3)
		- k2*_q(n2,1)*_q(n3+n5,2)*_q(n1+n4+n6,3)
		+ 4.*_q(n2+n3+n5,3)*_q(n1+n4+n6,3)
		+ k2*_q(n1,1)*_q(n3,1)*_q(n5,1)*_q(n2+n4+n6,3)
		- k2*_q(n1+n3,2)*_q(n5,1)*_q(n2+n4+n6,3)
		- k2*_q(n3,1)*_q(n1+n5,2)*_q(n2+n4+n6,3)
		- k2*_q(n1,1)*_q(n3+n5,2)*_q(n2+n4+n6,3)
		+ 4.*_q(n1+n3+n5,3)*_q(n2+n4+n6,3)
		- k6*_q(n3,1)*_q(n5,1)*_q(n1+n2+n4+n6,4)
		+ k6*_q(n3+n5,2)*_q(n1+n2+n4+n6,4)
		+ k2*_q(n1,1)*_q(n2,1)*_q(n5,1)*_q(n3+n4+n6,3)
		- k2*_q(n1+n2,2)*_q(n5,1)*_q(n3+n4+n6,3)
		- k2*_q(n2,1)*_q(n1+n5,2)*_q(n3+n4+n6,3)
		- k2*_q(n1,1)*_q(n2+n5,2)*_q(n3+n4+n6,3)
		+ 4.*_q(n1+n2+n5,3)*_q(n3+n4+n6,3)
		- k6*_q(n2,1)*_q(n5,1)*_q(n1+n3+n4+n6,4)
		+ k6*_q(n2+n5,2)*_q(n1+n3+n4+n6,4)
		- k6*_q(n1,1)*_q(n5,1)*_q(n2+n3+n4+n6,4)
		+ k6*_q(n1+n5,2)*_q(n2+n3+n4+n6,4)
		- _q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n5+n6,2)
		+ _q(n1+n2,2)*_q(n3,1)*_q(n4,1)*_q(n5+n6,2)
		+ _q(n2,1)*_q(n1+n3,2)*_q(n4,1)*_q(n5+n6,2)
		+ _q(n1,1)*_q(n2+n3,2)*_q(n4,1)*_q(n5+n6,2)
		- k2*_q(n1+n2+n3,3)*_q(n4,1)*_q(n5+n6,2)
		+ _q(n2,1)*_q(n3,1)*_q(n1+n4,2)*_q(n5+n6,2)
		- _q(n2+n3,2)*_q(n1+n4,2)*_q(n5+n6,2)
		+ _q(n1,1)*_q(n3,1)*_q(n2+n4,2)*_q(n5+n6,2)
		- _q(n1+n3,2)*_q(n2+n4,2)*_q(n5+n6,2)
		- k2*_q(n3,1)*_q(n1+n2+n4,3)*_q(n5+n6,2)
		+ _q(n1,1)*_q(n2,1)*_q(n3+n4,2)*_q(n5+n6,2)
		- _q(n1+n2,2)*_q(n3+n4,2)*_q(n5+n6,2)
		- k2*_q(n2,1)*_q(n1+n3+n4,3)*_q(n5+n6,2)
		- k2*_q(n1,1)*_q(n2+n3+n4,3)*_q(n5+n6,2)
		+ k6*_q(n1+n2+n3+n4,4)*_q(n5+n6,2)
		+ k2*_q(n2,1)*_q(n3,1)*_q(n4,1)*_q(n1+n5+n6,3)
		- k2*_q(n2+n3,2)*_q(n4,1)*_q(n1+n5+n6,3)
		- k2*_q(n3,1)*_q(n2+n4,2)*_q(n1+n5+n6,3)
		- k2*_q(n2,1)*_q(n3+n4,2)*_q(n1+n5+n6,3)
		+ 4.*_q(n2+n3+n4,3)*_q(n1+n5+n6,3)
		+ k2*_q(n1,1)*_q(n3,1)*_q(n4,1)*_q(n2+n5+n6,3)
		- k2*_q(n1+n3,2)*_q(n4,1)*_q(n2+n5+n6,3)
		- k2*_q(n3,1)*_q(n1+n4,2)*_q(n2+n5+n6,3)
		- k2*_q(n1,1)*_q(n3+n4,2)*_q(n2+n5+n6,3)
		+ 4.*_q(n1+n3+n4,3)*_q(n2+n5+n6,3)
		- k6*_q(n3,1)*_q(n4,1)*_q(n1+n2+n5+n6,4)
		+ k6*_q(n3+n4,2)*_q(n1+n2+n5+n6,4)
		+ k2*_q(n1,1)*_q(n2,1)*_q(n4,1)*_q(n3+n5+n6,3)
		- k2*_q(n1+n2,2)*_q(n4,1)*_q(n3+n5+n6,3)
		- k2*_q(n2,1)*_q(n1+n4,2)*_q(n3+n5+n6,3)
		- k2*_q(n1,1)*_q(n2+n4,2)*_q(n3+n5+n6,3)
		+ 4.*_q(n1+n2+n4,3)*_q(n3+n5+n6,3)
		- k6*_q(n2,1)*_q(n4,1)*_q(n1+n3+n5+n6,4)
		+ k6*_q(n2+n4,2)*_q(n1+n3+n5+n6,4)
		- k6*_q(n1,1)*_q(n4,1)*_q(n2+n3+n5+n6,4)
		+ k6*_q(n1+n4,2)*_q(n2+n3+n5+n6,4)
		+ k2*_q(n1,1)*_q(n2,1)*_q(n3,1)*_q(n4+n5+n6,3)
		- k2*_q(n1+n2,2)*_q(n3,1)*_q(n4+n5+n6,3)
		- k2*_q(n2,1)*_q(n1+n3,2)*_q(n4+n5+n6,3)
		- k2*_q(n1,1)*_q(n2+n3,2)*_q(n4+n5+n6,3)
		+ 4.*_q(n1+n2+n3,3)*_q(n4+n5+n6,3)
		- k6*_q(n2,1)*_q(n3,1)*_q(n1+n4+n5+n6,4)
		+ k6*_q(n2+n3,2)*_q(n1+n4+n5+n6,4)
		- k6*_q(n1,1)*_q(n3,1)*_q(n2+n4+n5+n6,4)
		+ k6*_q(n1+n3,2)*_q(n2+n4+n5+n6,4)
		- k6*_q(n1,1)*_q(n2,1)*_q(n3+n4+n5+n6,4)
		+ k6*_q(n1+n2,2)*_q(n3+n4+n5+n6,4)
		+ k24*_q(n5,1)*_q(n1+n2+n3+n4+n6,5)
		+ k24*_q(n4,1)*_q(n1+n2+n3+n5+n6,5)
		+ k24*_q(n3,1)*_q(n1+n2+n4+n5+n6,5)
		+ k24*_q(n2,1)*_q(n1+n3+n4+n5+n6,5)
		+ k24*_q(n1,1)*_q(n2+n3+n4+n5+n6,5)
		- k120*_q(n1+n2+n3+n4+n5+n6,6));
      }
  }
}
// Local Variables:
//  mode: C++
// End:
