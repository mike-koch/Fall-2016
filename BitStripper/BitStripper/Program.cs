using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BitStripper {
    class Program {
        static void Main(string[] args) {
            const int MB_IN_BYTES = 1048576;
            string inputFilePath = @"C:\Users\Mike\Desktop\Security Challenge\ChallengeDisc1.wav"; //args[0];
            string outputFilePath = @"C:\Users\Mike\Desktop\testOutput.txt"; //args[1];
            string numberOfBitsToKeep = "1"; //args[2];

            using (var outputFileStream = new FileStream(outputFilePath, FileMode.Create, FileAccess.ReadWrite)) {
                int numberOfBytesWritten = 0;

                using (var fileStream = new FileStream(inputFilePath, FileMode.Open, FileAccess.Read)) {
                    long numberOfBytesInFile = fileStream.Length;
                    var tempResultingBuffer = new List<bool>();

                    int numberOfBytesRead = 0;

                    while (numberOfBytesInFile - numberOfBytesRead > 0) {
                        var buffer = new byte[MB_IN_BYTES];
                        int numberOfBytesReadThisIteration = fileStream.Read(buffer, numberOfBytesRead, MB_IN_BYTES);

                        if (numberOfBytesReadThisIteration == 0) {
                            //-- We've reached the end of the file
                            break;
                        }

                        tempResultingBuffer.AddRange(getBit(buffer, numberOfBitsToKeep));

                        //-- Write any whole bytes out to the output buffer. This way we won't keep too much information in memory.
                        byte[] resultingBuffer = transformToResultingBuffer(tempResultingBuffer);

                        outputFileStream.Write(resultingBuffer, numberOfBytesWritten, resultingBuffer.Length);
                        numberOfBytesWritten += resultingBuffer.Length;

                        numberOfBytesRead += numberOfBytesReadThisIteration;
                    }
                }
            }
        }

        //-- Returns a list of bits that should be appended to the byte stream. These are the last N bits from each byte
        private static List<bool> getBit(byte[] buffer, string bitNumber) {
            int bitToGet = int.Parse(bitNumber);

            var keptBits = new List<bool>();
            foreach (byte theByte in buffer) {
                keptBits.Add(1 == ((theByte >> bitToGet - 1) & 1));
            }

            return keptBits;
        }

        //-- Converts from the bool list to the byte list to be processed in the output filestream
        private static byte[] transformToResultingBuffer(List<bool> tempResultingBuffer) {
            const int minimumNumberOfBitsToMakeAByte = 8;
            var resultingBuffer = new List<byte>();
            while (tempResultingBuffer.Count >= minimumNumberOfBitsToMakeAByte) {
                //-- Get the next 8 "bits". We know there are enough elements in the list, so we don't need to worry about going out of range.
                BitArray bitArray = new BitArray(new [] {new byte()});
                for (int i = 0; i < 8; i++) {
                    bitArray.Set(7 - i, tempResultingBuffer[i]);
                }

                //-- Copy the bit array to the resultingBuffer.
                resultingBuffer.Add(convertBitArrayToByte(bitArray));

                //-- Remove the elements from the temp buffer
                tempResultingBuffer.RemoveRange(0, 8);
            }

            //-- Now that we have the bytes in a list, just convert them to an array.
            return resultingBuffer.ToArray();
        }

        private static byte convertBitArrayToByte(BitArray bitArray) {
            var convertedByte = new byte[1];
            bitArray.CopyTo(convertedByte, 0);
            return convertedByte[0];
        }
    }
}
