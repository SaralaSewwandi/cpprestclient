#include "calculator.h"
#include <cpprest\filestream.h>

int __stdcall add(int a, int b)
{
	return a + b;
}

void __stdcall saveResponse()
{
	auto fileStream = std::make_shared<Concurrency::streams::ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = Concurrency::streams::fstream::open_ostream(U("prediction.json"))

		// Make a GET request.
		.then([=](Concurrency::streams::ostream outFile) {
		*fileStream = outFile;

		// Create http_client to send the request.
		http_client client(U("http://127.0.0.1:5000"));

		// Build request URI and start the request.
		return client.request(methods::GET, uri_builder(U("api")).append_path(U("forex")).append_path(U("prediction")).to_string());
			})

		// Get the response.
				.then([=](http_response response) {
				// Check the status code.
				if (response.status_code() != 200) {
					throw std::runtime_error("Returned " + std::to_string(response.status_code()));
				}

				// Write the response body to file stream.
				response.body().read_to_end(fileStream->streambuf()).wait();

				// Close the file.
				return fileStream->close();
					});

			// Wait for the concurrent tasks to finish.
			try {
				while (!requestTask.is_done()) { std::cout << "."; }
			}
			catch (const std::exception& e) {
				printf("Error exception:%s\n", e.what());
			}
}
