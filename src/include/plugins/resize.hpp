/*
 * Copyright (c) 2018 Preferred Networks, Inc. All rights reserved.
 */

#pragma once

#include <chainer_trt/plugin.hpp>

namespace chainer_trt {
namespace plugin {
    class resize : public plugin_base<resize> {
        int n_channels, in_h, in_w, out_h, out_w;
        nvinfer1::Dims dims;

        int in_size, out_size, u_size;
        int* d_dms;
        float* d_u;
        float* d_v;

    public:
        resize(int _n_channels, int _in_h, int _in_w, int _out_h, int _out_w);
        resize(const void* buf, size_t size);
        static nvinfer1::ILayer*
        build_layer(network_def network, const picojson::object& layer_params,
                    nvinfer1::DataType dt, const name_tensor_map& tensor_names,
                    const std::string& model_dir);

        size_t getSerializationSize() override { return sizeof(resize); }

        int initialize() override;
        void terminate() override;
        int enqueue(int batchSize, const void* const* inputs, void** outputs,
                    void* workspace, cudaStream_t stream) override;
        nvinfer1::Dims getOutputDimensions(int index,
                                           const nvinfer1::Dims* inputs,
                                           int nbInputDims) override;
        void serialize(void* buf);
    };
}
}
