
#
# Angular project build generator
#

configure_file(angular.json angular.json COPYONLY)
configure_file(package.json package.json COPYONLY)
configure_file(tsconfig.json tsconfig.json COPYONLY)

add_subdirectory(src)
