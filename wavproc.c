#include <stdio.h>
#define MODE 1
int check (int a,int b,int c,int d,int a1,int b1,int c1,int d1) {       //Function that checks if data is identical with the correct format of WAVE files
    if (a == a1 && b == b1 && c == c1 && d == d1) {
        return -1;
    }
    else {
        return 0;
    }
}
int combine2 (int a, int b) {       //Function that combines two elements and extracts information about the WAVE file that we need
    int result;
    result = (a << 8) | b;      //Moves the bits of the number to the left and adds the second number to the right, also it converts little-endian to big-endian
    return result;
}
int combine4 (int a, int b, int c, int d) {     //Function that combines four elements and extracts information about the WAVE file that we need
    int result;
    result = (a << 24) | (b << 16) | (c << 8) | d;      //It works like the function "combine2" but with 4 numbers
    return result;
}
int main(void) {
    if (MODE >= 1 && MODE <= 6) {    
        int noRiff, noWave, noFmt, noData, sumData, lowVolume, lowFirst, lowSecond, lowThird, lowFourth, mode4block, mode4data, Data, WaveFormat, fmt, Wave, RIFF, k, aa, bb, cc ,dd, data, size, sr1, sr2, sr3, sr4, bps1, bps2, bps3, bps4, sample, bytes, ch, ch1, ch2, ch3, ch4, ExtraData, x, sum, SizeOfFile, format, MonoStereo, SampleRate, BytesPerSec, BlockAlign, BitsPerSample, SizeOfData;
        sum = 0;
        ExtraData = 0;      //Integer that checks if Extra data are correct
        sumData = 0;    //Integer that checks if there is an Insufficient data error
        noData = 0;     //Integer that checks if "data" is correct
        noFmt = 0;      //Integer that checks if "fmt " is correct
        noRiff = 0;     //Integer that checks if "RIFF" is correct
        noWave = 0;     //Integer that checks if "WAVE" is correct
        for (x = 0; ; x++) {
            ch = getchar();
            if (ch == EOF) {
                break;      //Stop after EOF
            }
            if (x > 7) {        //Start counting bytes after RIFF and SizeOfFile to check if there is a Bad size file error
                sum++; 
            }
            if (x < 44) {       //The first 44 bytes are those we need to check
                if (x == 0 || x == 4 || x == 8 || x == 12 || x == 16 || x == 20 || x == 24 || x == 28 || x == 32 || x == 36 || x == 40) {       //Positions that important data exists
                    ch1 = ch;       //We store the value that we got from the .wav file
                }
                if (x == 1 || x == 5 || x == 9 || x == 13 || x == 17 || x == 21 || x == 25 || x == 29 || x == 33 || x == 37 || x == 41) {       //Positions that important data exists
                    ch2 = ch;       //We store the value that we got from the .wav file
                    if (x == 21) {      
                        WaveFormat = combine2(ch2,ch1);    
                    }
                    if (x == 33) {
                        BlockAlign = combine2(ch2,ch1);     
                    }
                }
                if (x == 2 || x == 6 || x == 10 || x == 14 || x == 18 || x == 22 || x == 26 || x == 30 || x == 34 || x == 38 || x == 42) {      //Positions that important data exists
                    ch3 = ch;       //We store the value that we got from the .wav file
                }
                if (x == 3 || x == 7 || x == 11 || x == 15 || x == 19 || x == 23 || x == 27 || x == 31 || x == 35 || x == 39 || x == 43) {      //Positions that important data exists
                    ch4 = ch;       //We store the value that we got from the .wav file
                    if (x == 3) {
                        if (!check(ch1, ch2, ch3, ch4,'R','I','F','F')) {
                            noRiff = 1;
                        }
                        RIFF = combine4(ch4, ch3, ch2, ch1);
                    }
                    if (x == 7) {
                        SizeOfFile = combine4(ch4, ch3, ch2, ch1); 
                    }
                    if (x == 11) {
                        if (!check(ch1, ch2, ch3, ch4,'W','A','V','E')) {
                            noWave = 1;
                        }
                        Wave = combine4(ch4, ch3, ch2, ch1);
                    }
                    if (x == 15) {
                        if (!check(ch1, ch2, ch3, ch4,'f','m','t',32)) {
                            noFmt = 1;
                        }
                        fmt = combine4(ch4, ch3, ch2, ch1);                        
                    }
                    if (x == 19) {
                        format = combine4(ch4, ch3, ch2, ch1);      
                    }
                    if (x == 23) {
                        MonoStereo = combine2(ch4,ch3);     
                    }
                    if (x == 27) {
                            SampleRate = combine4(ch4, ch3, ch2, ch1);
                            if (MODE == 2) {
                                sample = SampleRate / 2;        //Divide SampleRate by 2 so we have x0.5 the speed we had
                                sr1 = (sample >> 24) & 0xFF;        //Converting the divided number into 4 bytes
                                sr2 = (sample >> 16) & 0xFF;
                                sr3 = (sample >> 8) & 0xFF;
                                sr4 = sample & 0xFF;
                            }
                            else if (MODE == 3) {
                                sample = SampleRate * 2;        //Multiply SampleRate by 2 so we have x2 the speed we had
                                sr1 = (sample >> 24) & 0xFF;        //Converting the multiplied number into 4 bytes
                                sr2 = (sample >> 16) & 0xFF;
                                sr3 = (sample >> 8) & 0xFF;
                                sr4 = sample & 0xFF;
                            }
                    }
                    if (x == 31) {
                            BytesPerSec = combine4(ch4, ch3, ch2, ch1);
                            if (MODE == 2) {
                                bytes = BytesPerSec / 2;        //Divide the number so we have x0.5 the speed we had
                                bps1 = (bytes >> 24) & 0xFF;        //Converting the divided number into 4 bytes
                                bps2 = (bytes >> 16) & 0xFF;
                                bps3 = (bytes >> 8) & 0xFF;
                                bps4 = bytes & 0xFF;
                            }
                            else if (MODE == 3) {
                                bytes = BytesPerSec * 2;        //Multiply BytesPerSec by 2 so we have x2 the speed we had
                                bps1 = (bytes >> 24) & 0xFF;        //Converting the multiplied number into 4 bytes
                                bps2 = (bytes >> 16) & 0xFF;
                                bps3 = (bytes >> 8) & 0xFF;
                                bps4 = bytes & 0xFF;
                            }
                    }
                    if (x == 35) {
                        BitsPerSample = combine2(ch4,ch3);
                    }
                    if (x == 39) {
                        if (!check(ch1, ch2, ch3, ch4,'d','a','t','a')) {
                            noData = 1;
                        } 
                        Data = combine4(ch4, ch3, ch2, ch1);
                    }
                    if (x == 43) {
                        SizeOfData = combine4(ch4, ch3, ch2, ch1);                
                    }
                }
            }
            if (x == 43) {     //After storing SizeOfData and after the amount of the bytes we are interested plus the amount of SizeOfData count Extra Data
                ExtraData = SizeOfFile - SizeOfData - 36;       //Counts Extra data
            }
            if (sum >= 36 && sum < SizeOfFile - ExtraData) {
                if ( MODE < 4 || BitsPerSample == 8 || MODE == 6) {     //when MODE is 4 or 5, It checks for Insufficient error with another way
                    sumData++;      //Counting size of data chunk
                }
            }
            if (MODE == 2 || MODE == 3) {
                if (x == 31) {
                    putchar(sr4);       //Prints at stdout the data we converted into 4 bytes with putchar()
                    putchar(sr3);
                    putchar(sr2);
                    putchar(sr1);
                    putchar(bps4);
                    putchar(bps3);
                    putchar(bps2);
                    putchar(bps1);
                }
                if (x < 24 || x > 31) {
                    putchar(ch);        
                }
            }
            if (MODE == 4 || MODE == 5) {
                if (MonoStereo == 2 && x >= 43) {
                    if (x == 43) {
                        for (k = 1; k < 14 ; k++) {     //Putting the first 44 bytes that are necessary for the correct form of the Wave file
                            if (k == 1) {
                                aa = (RIFF >> 24) & 0xFF;
                                bb = (RIFF >> 16) & 0xFF;
                                cc = (RIFF >> 8) & 0xFF;
                                dd = RIFF & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 2) {
                                size = (SizeOfData / 2) + 36 + ExtraData;            
                                aa = (size >> 24) & 0xFF;
                                bb = (size >> 16) & 0xFF;
                                cc = (size >> 8) & 0xFF;
                                dd = size & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 3) {
                                aa = (Wave >> 24) & 0xFF;
                                bb = (Wave >> 16) & 0xFF;
                                cc = (Wave >> 8) & 0xFF;
                                dd = Wave & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 4) {
                                aa = (fmt >> 24) & 0xFF;
                                bb = (fmt >> 16) & 0xFF;
                                cc = (fmt >> 8) & 0xFF;
                                dd = fmt & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 5) {
                                aa = (format >> 24) & 0xFF;
                                bb = (format >> 16) & 0xFF;
                                cc = (format >> 8) & 0xFF;
                                dd = format & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 6) {
                                bb = WaveFormat & 0xFF;
                                aa = (WaveFormat >> 8) & 0xFF;
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 7) {
                                putchar(1);
                                putchar(0);
                            }
                            else if (k == 8) {
                                aa = (SampleRate >> 24) & 0xFF;
                                bb = (SampleRate >> 16) & 0xFF;
                                cc = (SampleRate >> 8) & 0xFF;
                                dd = SampleRate & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 9) {
                                bytes = BytesPerSec / 2;
                                aa = (bytes >> 24) & 0xFF;
                                bb = (bytes >> 16) & 0xFF;
                                cc = (bytes >> 8) & 0xFF;
                                dd = bytes & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 10) {
                                mode4block = BlockAlign / 2;
                                bb = mode4block & 0xFF;
                                aa = (mode4block >> 8) & 0xFF;
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 11) {
                                bb = BitsPerSample & 0xFF;
                                aa = (BitsPerSample >> 8) & 0xFF;
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 12) {
                                aa = (Data >> 24) & 0xFF;
                                bb = (Data >> 16) & 0xFF;
                                cc = (Data >> 8) & 0xFF;
                                dd = Data & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }
                            else if (k == 13) {
                                mode4data = SizeOfData / 2;
                                aa = (mode4data >> 24) & 0xFF;
                                bb = (mode4data >> 16) & 0xFF;
                                cc = (mode4data >> 8) & 0xFF;
                                dd = mode4data & 0xFF;
                                putchar(dd);
                                putchar(cc);
                                putchar(bb);
                                putchar(aa);
                            }                                                
                        }
                    }
                    else if (x > 43 && BitsPerSample == 8 && x <= (SizeOfData + 44)) {      //Only for BitsPerSample == 8
                        if (x % 2 == 0 && MODE == 4) {      //If MODE == 4 put only the left channel of the file
                            putchar(ch);
                        }
                        else if (x % 2 != 0 && MODE == 5) {     //If MODE == 5 put only the right channel of the file
                            putchar(ch);
                        }
                    }
                    else if (x > (SizeOfData + 44 & BitsPerSample == 8)) {
                        putchar(ch);        //Puts ExtraData for files with BitsPerSample == 8
                    }
                }
                else if (MonoStereo == 1 && x == 23) {      //If there is only one channel put the bytes without changing them
                    for (k = 1; k < 8 ; k++) {
                        if (k == 1) {
                            aa = (RIFF >> 24) & 0xFF;
                            bb = (RIFF >> 16) & 0xFF;
                            cc = (RIFF >> 8) & 0xFF;
                            dd = RIFF & 0xFF;
                            putchar(dd);
                            putchar(cc);
                            putchar(bb);
                            putchar(aa);
                        }
                        else if (k == 2) {            
                            aa = (SizeOfFile >> 24) & 0xFF;
                            bb = (SizeOfFile >> 16) & 0xFF;
                            cc = (SizeOfFile >> 8) & 0xFF;
                            dd = SizeOfFile & 0xFF;
                            putchar(dd);
                            putchar(cc);
                            putchar(bb);
                            putchar(aa);
                        }
                        else if (k == 3) {
                            aa = (Wave >> 24) & 0xFF;
                            bb = (Wave >> 16) & 0xFF;
                            cc = (Wave >> 8) & 0xFF;
                            dd = Wave & 0xFF;
                            putchar(dd);
                            putchar(cc);
                            putchar(bb);
                            putchar(aa);
                        }
                        else if (k == 4) {
                            aa = (fmt >> 24) & 0xFF;
                            bb = (fmt >> 16) & 0xFF;
                            cc = (fmt >> 8) & 0xFF;
                            dd = fmt & 0xFF;
                            putchar(dd);
                            putchar(cc);
                            putchar(bb);
                            putchar(aa);
                        }
                        else if (k == 5) {
                            aa = (format >> 24) & 0xFF;
                            bb = (format >> 16) & 0xFF;
                            cc = (format >> 8) & 0xFF;
                            dd = format & 0xFF;
                            putchar(dd);
                            putchar(cc);
                            putchar(bb);
                            putchar(aa);
                        }
                        else if (k == 6) {
                            bb = WaveFormat & 0xFF;
                            aa = (WaveFormat >> 8) & 0xFF;
                            putchar(bb);
                            putchar(aa);
                        }
                        else if (k == 7) {
                            putchar(1);
                            putchar(0);
                        }
                    }             
                }
                else if (MonoStereo == 1 && x > 23) {
                    putchar(ch);
                } 
            } 
            if (MODE == 4 || MODE == 5) {
                if (MonoStereo == 2 && x > 43 && BitsPerSample == 16) {     //If BitsPerSample == 16 
                    if (x <= (SizeOfData + 44)) {
                        if (MODE == 4) {        //MODE == 4
                            putchar(ch);
                            if (x < (SizeOfData + 44)) {
                                sumData++;
                            }
                            if (x % 2 != 0) {       //Putting the first 2 bytes (left channel), and avoiding the next 2 bytes
                                ch = getchar();
                                x++;
                                sum++;
                                if (x <= (SizeOfData + 44)) {        //If x > (SizeOfData + 44) we have ExtraData 
                                    sumData++;
                                }
                                if (x <= (SizeOfData + 44)) {       //If x > (SizeOfData + 44) we have ExtraData 
                                    ch = getchar();
                                    x++;
                                    sum++;
                                    if (x <= (SizeOfData + 44)) {
                                        sumData++;
                                    }
                                }
                            }
                        }
                        else if (MODE == 5) {
                            if (x == 44 || x == 45) {
                                putchar(ch);
                            }
                            if (x > 45 && x <= (SizeOfData + 44)) {
                                putchar(ch);
                                if (x <= (SizeOfData + 44)) {       //If x > (SizeOfData + 44) we have ExtraData
                                    sumData++;
                                }
                                if(x % 2 != 0) {
                                    ch = getchar();
                                    x++;
                                    sum++;
                                    if (x <= (SizeOfData + 44)) {   //If x > (SizeOfData + 44) we have ExtraData
                                        sumData++;
                                    }
                                    if (x <= (SizeOfData + 44)) {
                                        ch = getchar();
                                        x++;
                                        sum++;
                                        sumData++;
                                    }
                                }
                            }
                        }
                    } 
                    else if (x > (SizeOfData + 44)) {
                        putchar(ch);        //Puts Extra data for Files with BitsPerSample == 16
                    }
                }
            }
            if (MODE == 6) {
                if (x < 44) {       //Puts bytes that indicates Wave Format withouth changing them
                    putchar(ch);
                }
                else if(x >= 44 && x <= (SizeOfData + 44)) {
                    if (BitsPerSample == 8) {       //Reduces the volume for files with BitsPerSample == 8
                        putchar(ch/8);
                    }
                    else if (BitsPerSample == 16) {     //Reduces the volume for files with BitsPerSample == 16
                        if (x % 2 == 0) {
                            ch1 = ch;       //Storing the byte for the left chanel
                        }
                        else if (x % 2 != 0) {
                            ch2 = ch;       //Storing the byte for the right chanel
                            lowVolume = combine2(ch2,ch1);
                            lowVolume = (short) lowVolume / 8;      //Assign short for negative values
                            putchar(lowVolume & 0xFF);
                            putchar((lowVolume >> 8) & 0xFF);
                        }
                    }   
                }
                else if (x > (SizeOfData + 44)) {
                    putchar(ch);        //Puts ExtraData
                }
            }
        }
        if (noRiff == 1) {
            fprintf(stderr,"Error! \"RIFF\" not found\n");
            return -1;
        }
        fprintf (stderr,"Size of file: %d\n", SizeOfFile);
        if (noWave == 1) {
            fprintf(stderr,"Error! \"WAVE\" not found\n");
            return -1;
        }
        if (noFmt == 1) {
            fprintf(stderr,"Error! \"fmt \" not found\n");
            return -1;
        }
        fprintf (stderr,"Size of format chunk: %d\n", format);
        if (format != 16) {
            fprintf(stderr,"Error! Size of format chunk should be 16\n");
            return -1;
        }
        fprintf (stderr,"WAVE type format: %d\n", WaveFormat);
        if (WaveFormat != 1) {
            fprintf(stderr,"Error! WAVE type format should be 1\n");
            return -1;
        }
        fprintf (stderr,"Mono/Stereo: %d\n", MonoStereo);
        if (MonoStereo != 1 && MonoStereo != 2) {
            fprintf(stderr,"Error! Mono/Stereo should be 1 or 2\n");
            return -1;
        }
        fprintf (stderr,"Sample Rate: %d\n", SampleRate);
        fprintf (stderr,"Bytes/Sec: %d\n", BytesPerSec);
        fprintf (stderr,"Block Alignment: %d\n", BlockAlign);
        if (BlockAlign * SampleRate != BytesPerSec) {
            fprintf (stderr,"Error! Bytes/Second should be sample rate x block alignment\n");
            return -1;
        }
        fprintf (stderr,"Bits/Sample: %d\n", BitsPerSample);
        if (BitsPerSample != 8 && BitsPerSample != 16) {
            fprintf(stderr,"Error! Bits/Sample should be 8 or 16\n");
            return -1;
        }
        if (BlockAlign != BitsPerSample / 8 * MonoStereo) {
            fprintf(stderr,"Error! Block Alignment should be Bits per Sample / 8 x Mono/Stereo\n");
            return -1;
        }
        if (noData == 1) {
            fprintf(stderr,"Error! \"data\" not found\n");
            return -1;
        }
        fprintf (stderr,"Size of data chunk: %d\n", SizeOfData);
        if (SizeOfData != sumData) {
            fprintf(stderr,"Error! insufficient data : %d\n", sumData);
            return -1;
        }
        else if (sum != SizeOfFile) {
            fprintf(stderr,"Error! bad file size : sum %d : %d\n", sum, x);
            return -1;
        }
        return 0;
    }
}
