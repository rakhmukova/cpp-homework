#pragma once

#include <iostream>
#include <vector>
#include <functional>

template<typename InputT, typename OutputT>
OutputT sequentialMapReduce(const std::vector<InputT>& input,
                            const std::function<OutputT(InputT)>& map_func,
                            const std::function<OutputT(OutputT, OutputT)>& reduce_func,
                            const OutputT& neutral_element);

template<typename InputT, typename OutputT>
OutputT openmpMapReduce(const std::vector<InputT>& input,
                            const std::function<OutputT(InputT)>& map_func,
                            const std::function<OutputT(OutputT, OutputT)>& reduce_func,
                            const OutputT& neutral_element);
