
#include "core.hpp"
#include "tools.hpp"

#include "CLI/CLI.hpp"
#include <string>

using namespace sep;

int main(int argc, char *argv[]) {

	// 0. load config
	std::string file_path	   = "./model/TinyLlama_v1.1-1.1B-F32.gguf";
	int steps				   = 16;		 // number of steps to run for
	std::string prompt		   = "One day,"; // prompt string

	CLI::App app("Demo program for llama");

	app.add_option("--file-path", file_path)->required();
	app.add_option("--prompt", prompt)->required();
	app.add_option("--steps", steps)->required();
	CLI11_PARSE(app, argc, argv);

	// 1. load model
	Transformer transformer(file_path);

	// 2. load tokenizer
	Tokenizer tokenizer(transformer.gguf_ctx_);

	// 3. load sampler
	Sampler sampler(transformer.config->vocab_size);

	// 4. generate tokens
	transformer.generate(&tokenizer, &sampler, prompt, steps);
}