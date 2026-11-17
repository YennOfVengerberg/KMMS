#include "runtime.hpp"

#ifdef QT6_GUI
	#include "qt6_runtime.hpp"
#else
	#include "console_runtime.hpp"
#endif

std::unique_ptr<biv::Runtime> biv::create_runtime(
	int argc, char* argv[], int map_height, int map_width
) {
#ifdef QT6_GUI
	return std::make_unique<Qt6Runtime>(argc, argv);
#else
	return std::make_unique<ConsoleRuntime>(map_height, map_width);
#endif
}
