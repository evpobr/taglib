/***************************************************************************
    copyright           : (C) 2007 by Lukas Lalinsky
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


#include <id3v2synchdata.h>
#include <gtest/gtest.h>

using namespace std;
using namespace TagLib;

TEST(TestID3v2SynchData, test1)
{
  char data[] = { 0, 0, 0, 127 };
  ByteVector v(data, 4);

  EXPECT_EQ(ID3v2::SynchData::toUInt(v), (unsigned int)127);
  EXPECT_EQ(ID3v2::SynchData::fromUInt(127), v);
}

TEST(TestID3v2SynchData, test2)
{
  char data[] = { 0, 0, 1, 0 };
  ByteVector v(data, 4);

  EXPECT_EQ(ID3v2::SynchData::toUInt(v), (unsigned int)128);
  EXPECT_EQ(ID3v2::SynchData::fromUInt(128), v);
}

TEST(TestID3v2SynchData, test3)
{
  char data[] = { 0, 0, 1, 1 };
  ByteVector v(data, 4);

  EXPECT_EQ(ID3v2::SynchData::toUInt(v), (unsigned int)129);
  EXPECT_EQ(ID3v2::SynchData::fromUInt(129), v);
}

TEST(TestID3v2SynchData, testToUIntBroken)
{
  char data[] = { 0, 0, 0, (char)-1 };
  char data2[] = { 0, 0, (char)-1, (char)-1 };

  EXPECT_EQ((unsigned int)255, ID3v2::SynchData::toUInt(ByteVector(data, 4)));
  EXPECT_EQ((unsigned int)65535, ID3v2::SynchData::toUInt(ByteVector(data2, 4)));
}

TEST(TestID3v2SynchData, testToUIntBrokenAndTooLarge)
{
  char data[] = { 0, 0, 0, (char)-1, 0 };
  ByteVector v(data, 5);

  EXPECT_EQ((unsigned int)255, ID3v2::SynchData::toUInt(v));
}

TEST(TestID3v2SynchData, testDecode1)
{
  ByteVector a("\xff\x00\x00", 3);
  a = ID3v2::SynchData::decode(a);
  EXPECT_EQ((unsigned int)2, a.size());
  EXPECT_EQ(ByteVector("\xff\x00", 2), a);
}

TEST(TestID3v2SynchData, testDecode2)
{
  ByteVector a("\xff\x44", 2);
  a = ID3v2::SynchData::decode(a);
  EXPECT_EQ((unsigned int)2, a.size());
  EXPECT_EQ(ByteVector("\xff\x44", 2), a);
}

TEST(TestID3v2SynchData, testDecode3)
{
  ByteVector a("\xff\xff\x00", 3);
  a = ID3v2::SynchData::decode(a);
  EXPECT_EQ((unsigned int)2, a.size());
  EXPECT_EQ(ByteVector("\xff\xff", 2), a);
}

TEST(TestID3v2SynchData, testDecode4)
{
  ByteVector a("\xff\xff\xff", 3);
  a = ID3v2::SynchData::decode(a);
  EXPECT_EQ((unsigned int)3, a.size());
  EXPECT_EQ(ByteVector("\xff\xff\xff", 3), a);
}
