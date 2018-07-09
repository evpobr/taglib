SET(test_runner_SRCS
  main.cpp
  test_list.cpp
  test_map.cpp
  test_smartptr.cpp
  test_mpeg.cpp
  test_synchdata.cpp
  test_trueaudio.cpp
  test_bytevector.cpp
  test_bytevectorlist.cpp
  test_bytevectorstream.cpp
  test_string.cpp
  test_propertymap.cpp
  test_file.cpp
  test_fileref.cpp
  test_id3v1.cpp
  test_id3v2.cpp
  test_xiphcomment.cpp
  test_aiff.cpp
  test_riff.cpp
  test_ogg.cpp
  test_oggflac.cpp
  test_flac.cpp
  test_flacpicture.cpp
  test_flacunknownmetadatablock.cpp
  test_ape.cpp
  test_apetag.cpp
  test_wav.cpp
  test_info.cpp
  test_wavpack.cpp
  test_mp4.cpp
  test_mp4item.cpp
  test_mp4coverart.cpp
  test_asf.cpp
  test_mod.cpp
  test_s3m.cpp
  test_it.cpp
  test_xm.cpp
  test_mpc.cpp
  test_opus.cpp
  test_speex.cpp
  test_dsf.cpp
  test_matroska.cpp
)
ADD_EXECUTABLE(test_runner ${test_runner_SRCS})
target_include_directories(test_runner
  PRIVATE
    ${CPPUNIT_INCLUDE_DIR}
)
target_link_libraries(test_runner
  PRIVATE
    tag
	${CPPUNIT_LIBRARIES}
)

ADD_TEST(test_runner test_runner)
ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND} -V
                  DEPENDS test_runner)
