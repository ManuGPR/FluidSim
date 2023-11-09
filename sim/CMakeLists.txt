# Add to this list all files related to sim library
add_library(sim
        progargs.hpp
        progargs.cpp
        grid.hpp
        block.cpp
        block.hpp
        calculos.hpp
        calculos.cpp
        constants.hpp
        file.hpp
        file.cpp
        simulacion.cpp

)
# Use this line only if you have dependencies from stim to GSL
#target_link_libraries (sim PRIVATE Microsoft.GSL::GSL)