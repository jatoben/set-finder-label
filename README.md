# About set-finder-label #

`set-finder-label` is a small utility to set the Finder label of a file or set of files. This task typically involves AppleScripting the Finder, but in many automation scenarios, the Finder may not be running.

## System Requirements ##
`set-finder-label` requires Mac OS X 10.5+.

## Usage Example ##
    $ set-finder-label
    Usage: set-finder-label [label] [file1] [file2] ...
    Valid labels are none, gray, green, purple, blue, yellow, or red
    
    # Simple usage
    $ set-finder-label green ~/Documents
    $ set-finder-label red ~/Desktop/*.txt
    
    # If a file can't be found or an error occurs, set-finder-label reports the 
    # problem and continues processing the file list
    $ set-finder-label purple ~/Documents ~/FooBar ~/Desktop
    Error opening /Users/jatoben/FooBar: -43
    
    # Combine with find and xargs to label all old AppleWorks files
    # in all user home folders
    $ find /Users -name '*.cwk' -print0 | xargs -0 set-finder-label yellow
    
## License ##
Copyright (c) 2010 Ben Gollmer.

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.