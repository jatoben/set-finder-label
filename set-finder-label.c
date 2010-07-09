/*!
 * set-finder-label.c
 * set-finder-label
 *
 * Copyright (c) 2010 Ben Gollmer.
 * 
 * Docs on the FileInfo and FolderInfo structs can be found in
 * http://developer.apple.com/legacy/mac/library/documentation/Carbon/Reference/Finder_Interface/finder_interface.pdf
 * 
 * See also: FSCatalogInfo
 * http://developer.apple.com/mac/library/documentation/Carbon/Reference/File_Manager/Reference/reference.html#//apple_ref/doc/uid/TP30000107-CH3g-C008645
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <CoreServices/CoreServices.h>
#include <stdio.h>
#include <sys/stat.h>

typedef enum FinderLabels
{
  kFinderLabelNone    = 0,
  kFinderLabelGray    = 2,
  kFinderLabelGreen   = 4,
  kFinderLabelPurple  = 6,
  kFinderLabelBlue    = 8,
  kFinderLabelYellow  = 10,
  kFinderLabelRed     = 12,
  kFinderLabelInvalid = 255
} FinderLabel;

int main (int argc, const char *argv[])
{
  OSErr err;
  FSRef ref;
  FinderLabel label = kFinderLabelInvalid;
  struct stat stbuf;
  FSCatalogInfo info;
  int ret = 0;
  
  if(argc < 3)
  {
    fprintf(stderr, "Usage: set-finder-label [label] [file1] [file2] ...\n"
       "Valid labels are none, gray, green, purple, blue, yellow, or red\n");
    return -1;
  }
  
  if(strcmp(argv[1], "none") == 0)
  {
    label = kFinderLabelNone;
  }
  else if(strcmp(argv[1], "gray") == 0)
  {
    label = kFinderLabelGray;
  }
  else if(strcmp(argv[1], "green") == 0)
  {
    label = kFinderLabelGreen;
  }
  else if(strcmp(argv[1], "purple") == 0)
  {
    label = kFinderLabelPurple;
  }
  else if(strcmp(argv[1], "blue") == 0)
  {
    label = kFinderLabelBlue;
  }
  else if(strcmp(argv[1], "yellow") == 0)
  {
    label = kFinderLabelYellow;
  }
  else if(strcmp(argv[1], "red") == 0)
  {
    label = kFinderLabelRed;
  }
  
  if(label == kFinderLabelInvalid)
  {
    fprintf(stderr, "Invalid label selection\n");
    return -1;
  }
  
  for(int i = 2; i < argc; i++)
  {    
    err = FSPathMakeRef((const unsigned char *)argv[i], &ref, NULL);
    if(err != noErr)
    {
      fprintf(stderr, "Error opening %s: %d\n", argv[i], err);
      ret = 1;
      continue;
    }
    
    stat(argv[i], &stbuf);
    if(S_ISREG(stbuf.st_mode))
    {
      FileInfo *finfo = (FileInfo *)info.finderInfo;
      finfo->finderFlags = (0x0001 + label);
      err = FSSetCatalogInfo(&ref, kFSCatInfoFinderInfo, &info);
    }
    else if(S_ISDIR(stbuf.st_mode))
    {
      FolderInfo *finfo = (FolderInfo *)info.finderInfo;
      finfo->finderFlags = (0x0001 + label);
      err = FSSetCatalogInfo(&ref, kFSCatInfoFinderInfo, &info);
    }
    else
    {
      fprintf(stderr, "%s must be a regular file or directory\n", argv[i]);
      ret = 1;
      continue;
    }
    
    if(err != noErr)
    {
      fprintf(stderr, "Error setting Finder label: %d\n", err);
      ret = err;
      continue;
    }
  }
  
  return ret;
}
