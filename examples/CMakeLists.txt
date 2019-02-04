########### next target ###############

add_executable(tagreader tagreader.cpp)
target_link_libraries(tagreader TagLib)

########### next target ###############

add_executable(tagreader_c tagreader_c.c)
target_link_libraries(tagreader_c TagLibC)

########### next target ###############

add_executable(tagwriter tagwriter.cpp)
target_link_libraries(tagwriter TagLib)

########### next target ###############

add_executable(framelist framelist.cpp)
target_link_libraries(framelist TagLib)

########### next target ###############

add_executable(strip-id3v1 strip-id3v1.cpp)
target_link_libraries(strip-id3v1 TagLib)

