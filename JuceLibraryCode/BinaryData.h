/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_27049036_INCLUDED
#define BINARYDATA_H_27049036_INCLUDED

namespace BinaryData
{
    extern const char*   addTrack_png;
    const int            addTrack_pngSize = 144;

    extern const char*   delete_png;
    const int            delete_pngSize = 498;

    extern const char*   pause_png;
    const int            pause_pngSize = 128;

    extern const char*   play_png;
    const int            play_pngSize = 515;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 4;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
