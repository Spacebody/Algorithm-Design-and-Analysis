
#include "Huffman.hpp"
using namespace std;
int main(int argc, char *argv[])
{
    if(argc != 4)
    {   //no input file
        cout<<"Error! Need inputfile outputfile"<<endl;
        exit(1);
    }
    //encode
    if(0 == strcmp("-e", argv[1]))
    {
        Huffman HF(argv[2], argv[3]);
        HF.Encode();
    }
    else if(0 == strcmp("-d", argv[1]))
    {   //decode
        Huffman HF(argv[2], argv[3]);
        HF.Decode();
    }
    else
    {   //if comman can't be recognized.
        cout<<"Sorry! Unkonwn command"<<endl;
        exit(1);
    }
    return 0;
}