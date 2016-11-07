using System;
using System.IO;
using System.Text;

namespace DigraphTrigraphAnalysis {
    internal class Analyzer {
        // Keep track of letter frequencies, digraphs, and trigraphs. I originally had a more OO approach, but performance was AWFUL when working with the encrypted text.
        private static readonly int[] characterFrequencies = new int[256];
        private static readonly int[,] digraphs = new int[256, 256];
        private static readonly int[,,] trigraphs = new int[256, 256, 256];

        private static void Main() {
            // Initialize arrays
            for (var i = 0; i < 256; i++) {
                for (var j = 0; j < 256; j++) {
                    digraphs[i, j] = 0;

                    for (var k = 0; k < 256; k++) {
                        trigraphs[i, j, k] = 0;
                    }
                }
            }

            // The file we want to perform an analysis on. @"" strings are wonderful to use
            const string fileToInspect = @"C:\Users\Mike\Desktop\DES\Shakespeare.txt";

            using (var fs = new StreamReader(File.Open(fileToInspect, FileMode.Open), Encoding.ASCII)) {
                // Keep track of the previous two characters so proper digraphs and trigraphs can be built
                int thirdToLastCharacter = -1;
                int secondToLastCharacter = -1;

                // While we still have a character to read from the StreamReader...
                while (fs.Peek() >= 0) {
                    // Get the next byte from the FileStream and get its char value
                    int character = fs.Read();

                    // Print it out just so we can see where we are along the way
                    Console.Write((char) character);

                    //-- If we're parsing the plaintext and we find a non text character (such as space, new line, etc), reset and move on. Disable for encrypted file. This is done since
                    //   digraphs and trigraphs do not normally contain spaces when inspecting plaintext documents.
                    if (!isValidCharacter(character)) {
                        secondToLastCharacter = -1;
                        thirdToLastCharacter = -1;
                        continue;
                    }

                    characterFrequencies[character]++;

                    if (secondToLastCharacter > -1) {
                        digraphs[secondToLastCharacter, character]++;
                    }

                    if (thirdToLastCharacter > -1) {
                        trigraphs[thirdToLastCharacter, secondToLastCharacter, character]++;
                    }

                    thirdToLastCharacter = secondToLastCharacter;
                    secondToLastCharacter = character;
                }
            }

            const string outputFilePath = @"C:\Users\Mike\Desktop\DES\ShakespeareCharacteristicsTxt.csv";

            using (var fs = new StreamWriter(outputFilePath)) {
                fs.Write("Letter Frequencies,,\n");
                for (var i = 0; i < 256; i++) {
                    var character = (char) i;

                    fs.Write("\"" + character + "\"," + characterFrequencies[i] + Environment.NewLine);
                }

                fs.Write("Digraph,,\n");
                for (var i = 0; i < 256; i++) {
                    for (var j = 0; j < 256; j++) {
                        // If the digraph never occurs, don't output it
                        if (digraphs[i, j] == 0) {
                            continue;
                        }

                        var left = (char) i;
                        var right = (char) j;

                        // ReSharper disable RedundantToStringCallForValueType  (<-- just a comment for ReSharper to suppress a warning; feel free to ignore)
                        // I forcibly have to call .ToString() on each character, otherwise C# will implicitly convert them back to ints and output the sum, which isn't what I want.
                        fs.Write("\"" + left.ToString() + right.ToString() + "\"," + digraphs[i, j] +
                                 Environment.NewLine);
                    }
                }

                fs.Write("\n\nTrigraph,,\n");
                for (var i = 0; i < 256; i++) {
                    for (var j = 0; j < 256; j++) {
                        for (var k = 0; k < 256; k++) {
                            // If the trigraph never occurs, don't output it
                            if (trigraphs[i, j, k] == 0) {
                                continue;
                            }

                            var left = (char) i;
                            var center = (char) j;
                            var right = (char) k;
                            fs.Write("\"" + left.ToString().Replace("\"", "\\\"") +
                                     center.ToString().Replace("\"", "\\\"") + right.ToString().Replace("\"", "\\\"") +
                                     "\"," + trigraphs[i, j, k] + Environment.NewLine);
                        }
                    }
                }
            }
        }

        private static bool isValidCharacter(int character) {
            return character > 32 && character < 126;
        }
    }
}