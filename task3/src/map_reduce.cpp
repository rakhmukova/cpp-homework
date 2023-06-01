#include "map_reduce.h"

template<typename InputT, typename OutputT>
OutputT sequentialMapReduce(const std::vector<InputT>& input,
                            const std::function<OutputT(InputT)>& map_func,
                            const std::function<OutputT(OutputT, OutputT)>& reduce_func,
                            const OutputT& neutral_element){
    std::vector<OutputT> mapped(input.size());
    for (int i = 0; i < input.size(); ++i) {
        mapped[i] = map_func(input[i]);
    }

    OutputT result = neutral_element;
    for (int i = 0; i < mapped.size(); ++i) {
        result = reduce_func(result, mapped[i]);
    }

    return result;
}


template<typename InputT, typename OutputT>
OutputT openmpMapReduce(const std::vector<InputT>& input,
                            const std::function<OutputT(InputT)>& map_func,
                            const std::function<OutputT(OutputT, OutputT)>& reduce_func,
                            const OutputT& neutral_element) {
    OutputT total_result = neutral_element;
    #pragma omp parallel
    {
        OutputT local_result = neutral_element;

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < input.size(); ++i) {
            OutputT current_result = map_func(input[i]);
            local_result = reduce_func(local_result, current_result);
        }

        #pragma omp critical
        {
            total_result = reduce_func(total_result, local_result);
        }
    }

    return total_result;
}
