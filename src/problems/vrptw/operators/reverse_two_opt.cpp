/*

This file is part of VROOM.

Copyright (c) 2015-2018, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include <iostream>

#include "problems/vrptw/operators/reverse_two_opt.h"

namespace vroom {

vrptwReverseTwoOpt::vrptwReverseTwoOpt(const Input& input,
                                       const SolutionState& sol_state,
                                       TWRoute& tw_s_route,
                                       Index s_vehicle,
                                       Index s_rank,
                                       TWRoute& tw_t_route,
                                       Index t_vehicle,
                                       Index t_rank)
  : CVRPReverseTwoOpt(input,
                      sol_state,
                      static_cast<RawRoute&>(tw_s_route),
                      s_vehicle,
                      s_rank,
                      static_cast<RawRoute&>(tw_t_route),
                      t_vehicle,
                      t_rank),
    _tw_s_route(tw_s_route),
    _tw_t_route(tw_t_route) {
}

bool vrptwReverseTwoOpt::is_valid() {
  return CVRPReverseTwoOpt::is_valid() and
         _tw_t_route.is_valid_addition_for_tw(_input,
                                              s_route.rbegin(),
                                              s_route.rbegin() +
                                                s_route.size() - 1 - s_rank,
                                              0,
                                              t_rank + 1) and
         _tw_s_route.is_valid_addition_for_tw(_input,
                                              t_route.rbegin() +
                                                t_route.size() - 1 - t_rank,
                                              t_route.rend(),
                                              s_rank + 1,
                                              s_route.size());
}

void vrptwReverseTwoOpt::apply() {
  std::vector<Index> t_job_ranks;
  t_job_ranks.insert(t_job_ranks.begin(),
                     t_route.rbegin() + t_route.size() - 1 - t_rank,
                     t_route.rend());

  _tw_t_route.replace(_input,
                      s_route.rbegin(),
                      s_route.rbegin() + s_route.size() - 1 - s_rank,
                      0,
                      t_rank + 1);

  _tw_s_route.replace(_input,
                      t_job_ranks.begin(),
                      t_job_ranks.end(),
                      s_rank + 1,
                      s_route.size());
}

} // namespace vroom
