file(GLOB MoBaGEn_SRC
    "*.h"
    "*.cpp"
	"*.hpp"
    "*.cxx"
)

add_library(
		MoBaGEn STATIC
		${MoBaGEn_SRC}
)

