#include "GpuCollector.hpp"
namespace chameleon {
/*
 * functionName：get_gpu_string
 * description：Executing commands to obtain GPU information in the form of string
 * parameter: none
 * returnType: GPU information in the form of string
 */
    string GpuCollector::get_gpu_string() {
        Try<Subprocess> s = subprocess(
                "lshw -numeric -class video",
                Subprocess::FD(STDIN_FILENO),
                Subprocess::PIPE(),
                Subprocess::FD(STDERR_FILENO));
        Future<string> info = io::read(s.get().out().get());
        m_gpu_info = info.get();
        return m_gpu_info;
    }

/*
 * functionName：get_gpu_string
 * description：Separate and save the collected GPU information and encapsulate each information with protobuf
 * parameter: string m_gpu_info
 * returnType: void
 */
    void GpuCollector::split_gpu_string(string m_gpu_info) {
        vector<string> tokens = strings::split(m_gpu_info,
                                               "\n"); /*Divide gpu information from the command line by "\n" */
        vector<string>::iterator vec_iter;
        GpuInfo *gpuInfo;
        int index = 0; /*The number of GPU*/

        for (vec_iter = tokens.begin(); vec_iter != tokens.end(); vec_iter++) {
            if (strings::contains(*vec_iter, "display")) {
                index++;
            }
            std::string romove_bs = strings::trim(*vec_iter, " "); /*Remove spaces on both sides of each message*/
            vector<string> line_token = strings::tokenize(romove_bs, ":", 2); /*Separate each message with a ":" */

            for (vector<string>::iterator vec = line_token.begin(); vec != line_token.end(); vec++) {
                if (*vec == "description") {
                    gpuInfo = m_gpu_proto.add_gpu_infos();
                    gpuInfo->set_description(strings::trim(*(vec + 1),
                                                           " "));  /*Save the information that is the right of the ":" to the corresponding protobuf*/

                } else if (*vec == "product") {
                    gpuInfo->set_product(strings::trim(*(vec + 1), " "));
                } else if (*vec == "vendor") {
                    gpuInfo->set_vendor(strings::trim(*(vec + 1), " "));
                } else if (*vec == "physical id") {
                    gpuInfo->set_physical_id(strings::trim(*(vec + 1), " "));

                } else if (*vec == "bus info") {
                    gpuInfo->set_bus_info(strings::trim(*(vec + 1), " "));

                } else if (*vec == "version") {
                    gpuInfo->set_version(strings::trim(*(vec + 1), " "));
                } else if (*vec == "width") {
                    gpuInfo->set_width(strings::trim(*(vec + 1), " "));
                } else if (*vec == "clock") {
                    gpuInfo->set_clock(strings::trim(*(vec + 1), " "));

                } else if (*vec == "capabilities") {
                    gpuInfo->set_capabilities(strings::trim(*(vec + 1), " "));
                } else if (*vec == "configuration") {
                    gpuInfo->set_configuration(strings::trim(*(vec + 1), " "));
                } else if (*vec == "resources") {
                    gpuInfo->set_resources(strings::trim(*(vec + 1), " "));

                }

            }
        }
    }

    GPUCollection GpuCollector::get_gpu_proto() {
        return m_gpu_proto;
    }
}