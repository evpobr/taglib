/***************************************************************************
    copyright           : (C) 2009 by Lukas Lalinsky
    email               : lukas@oxygene.sk
 ***************************************************************************/

 /***************************************************************************
  *   This library is free software; you can redistribute it and/or modify  *
  *   it under the terms of the GNU Lesser General Public License version   *
  *   2.1 as published by the Free Software Foundation.                     *
  *                                                                         *
  *   This library is distributed in the hope that it will be useful, but   *
  *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
  *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
  *   Lesser General Public License for more details.                       *
  *                                                                         *
  *   You should have received a copy of the GNU Lesser General Public      *
  *   License along with this library; if not, write to the Free Software   *
  *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
  *   02110-1301  USA                                                       *
  *                                                                         *
  *   Alternatively, this file is available under the Mozilla Public        *
  *   License Version 1.1.  You may obtain a copy of the License at         *
  *   http://www.mozilla.org/MPL/                                           *
  ***************************************************************************/

#include <string>
#include <stdio.h>
#include <tag.h>
#include <tbytevectorlist.h>
#include <aifffile.h>
#include <gtest/gtest.h>
#include "utils.h"

using namespace std;
using namespace TagLib;

TEST(TestAIFF, testAiffProperties)
{
  RIFF::AIFF::File f(TEST_FILE_PATH_C("empty.aiff"));
  EXPECT_TRUE(f.audioProperties() != NULL);
  EXPECT_EQ(0, f.audioProperties()->length());
  EXPECT_EQ(0, f.audioProperties()->lengthInSeconds());
  EXPECT_EQ(67, f.audioProperties()->lengthInMilliseconds());
  EXPECT_EQ(706, f.audioProperties()->bitrate());
  EXPECT_EQ(44100, f.audioProperties()->sampleRate());
  EXPECT_EQ(1, f.audioProperties()->channels());
  EXPECT_EQ(16, f.audioProperties()->bitsPerSample());
  EXPECT_EQ(16, f.audioProperties()->sampleWidth());
  EXPECT_EQ(2941U, f.audioProperties()->sampleFrames());
  EXPECT_EQ(false, f.audioProperties()->isAiffC());
}

TEST(TestAIFF, testAiffCProperties)
{
  RIFF::AIFF::File f(TEST_FILE_PATH_C("alaw.aifc"));
  EXPECT_TRUE(f.audioProperties() != NULL);
  EXPECT_EQ(0, f.audioProperties()->length());
  EXPECT_EQ(0, f.audioProperties()->lengthInSeconds());
  EXPECT_EQ(37, f.audioProperties()->lengthInMilliseconds());
  EXPECT_EQ(355, f.audioProperties()->bitrate());
  EXPECT_EQ(44100, f.audioProperties()->sampleRate());
  EXPECT_EQ(1, f.audioProperties()->channels());
  EXPECT_EQ(16, f.audioProperties()->bitsPerSample());
  EXPECT_EQ(16, f.audioProperties()->sampleWidth());
  EXPECT_EQ(1622U, f.audioProperties()->sampleFrames());
  EXPECT_EQ(true, f.audioProperties()->isAiffC());
  EXPECT_EQ(ByteVector("ALAW"), f.audioProperties()->compressionType());
  EXPECT_EQ(String("SGI CCITT G.711 A-law"), f.audioProperties()->compressionName());
}

TEST(TestAIFF, testSaveID3v2)
{
  ScopedFileCopy copy("empty", ".aiff");
  string newname = copy.fileName();

  {
    RIFF::AIFF::File f(newname.c_str());
    EXPECT_FALSE(f.hasID3v2Tag());

    f.tag()->setTitle(L"TitleXXX");
    f.save();
    EXPECT_TRUE(f.hasID3v2Tag());
  }
  {
    RIFF::AIFF::File f(newname.c_str());
    EXPECT_TRUE(f.hasID3v2Tag());
    EXPECT_EQ(String(L"TitleXXX"), f.tag()->title());

    f.tag()->setTitle("");
    f.save();
    EXPECT_FALSE(f.hasID3v2Tag());
  }
  {
    RIFF::AIFF::File f(newname.c_str());
    EXPECT_FALSE(f.hasID3v2Tag());
  }
}

TEST(TestAIFF, testDuplicateID3v2)
{
  ScopedFileCopy copy("duplicate_id3v2", ".aiff");

  // duplicate_id3v2.aiff has duplicate ID3v2 tag chunks.
  // title() returns "Title2" if can't skip the second tag.

  RIFF::AIFF::File f(copy.fileName().c_str());
  EXPECT_TRUE(f.hasID3v2Tag());
  EXPECT_EQ(String("Title1"), f.tag()->title());

  f.save();
  EXPECT_EQ(7030L, f.length());
  EXPECT_EQ(-1L, f.find("Title2"));
}

TEST(TestAIFF, testFuzzedFile1)
{
  RIFF::AIFF::File f(TEST_FILE_PATH_C("segfault.aif"));
  EXPECT_FALSE(f.isValid());
}

TEST(TestAIFF, testFuzzedFile2)
{
  RIFF::AIFF::File f(TEST_FILE_PATH_C("excessive_alloc.aif"));
  EXPECT_FALSE(f.isValid());
}
