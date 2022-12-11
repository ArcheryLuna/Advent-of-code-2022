using System;
using System.Collections.Generic;
using System.Linq;

public class Day7 {
    static void PartOne(dynamic input) {
        var currentDirectory = new List<string>();

        string createCurrentDirectory(){
            string dir = string.Join("/",currentDirectory);
            dir = dir.Replace("//", "/");
            return dir;
        }

        var directorySize = new Dictionary<string,int>();

        foreach (var line in input){
            if (line.Substring(0,1) == "$"){
                var command = line.Split(" ");

                switch (command[1]) {
                    case "cd":
                        switch(command[2]){
                            case "..":
                                currentDirectory.RemoveAt(currentDirectory.Count-1);
                                // Console.WriteLine("Changing directory to: " + createCurrentDirectory());
                                break;
                            default:
                                currentDirectory.Add(command[2]);
                                // Console.WriteLine("Changing directory to: " + createCurrentDirectory());
                                break;
                        }
                        break;
                    case "ls":
                        // Console.WriteLine("Reading directory: " + createCurrentDirectory());
                        break;
                    default:
                        // Console.WriteLine("Unknown command: " + command[1]);
                        break;

                }
            }
            else if (line.Substring(0,3) != "dir"){
                var file = line.Split(" ");

                if (!directorySize.ContainsKey(createCurrentDirectory())){
                    directorySize[createCurrentDirectory()] = 0;
                }

                string dir = createCurrentDirectory();

                while (dir.Contains("/")){

                    if (!directorySize.ContainsKey(dir)){
                        directorySize[dir] = 0;
                    }

                    directorySize[dir] += Convert.ToInt32(file[0]);

                    if (dir == "/") break;

                    var dirSplit = dir.Split("/").ToList();
                    dirSplit.RemoveAt(dirSplit.Count-1);
                    dir = string.Join("/",dirSplit);
                }
            }
        }

        int output = 0;

        foreach(var item in directorySize)
        {
            if (item.Value <= 100000){
                output += item.Value;
            }
        }

        Console.WriteLine($"Part One: {output.ToString()}");
    }

    static void PartTwo(dynamic input) {
        var currentDirectory = new List<string>();

        string createCurrentDirectory(){
            string dir = string.Join("/",currentDirectory);
            dir = dir.Replace("//", "/");
            return dir;
        }

        var directorySize = new Dictionary<string,int>(){
            {"/",0}
        };

        foreach (var line in input){
            if (line.Substring(0,1) == "$"){
                var command = line.Split(" ");

                switch (command[1]) {
                    case "cd":
                        switch (command[2])
                        {
                            case "..":
                                currentDirectory.RemoveAt(currentDirectory.Count - 1);
                                // Console.WriteLine("Changing directory to: " + createCurrentDirectory());
                                break;
                            default:
                                currentDirectory.Add(command[2]);
                                // Console.WriteLine("Changing directory to: " + createCurrentDirectory());
                                break;
                        }
                        break;
                    case "ls":
                        // Console.WriteLine("Reading directory: " + createCurrentDirectory());
                        break;
                    default:
                        // Console.WriteLine("Unknown command: " + command[1]);
                        break;
                }
            }
            else if (line.Substring(0,3) != "dir"){
                var file = line.Split(" ");

                if (!directorySize.ContainsKey(createCurrentDirectory())){
                    directorySize[createCurrentDirectory()] = 0;
                }

                string dir = createCurrentDirectory();
                directorySize["/"] += Convert.ToInt32(file[0]);

                while (dir.Contains("/")){
                    if (!directorySize.ContainsKey(dir)){
                        directorySize[dir] = 0;
                    }
                    
                    directorySize[dir] += Convert.ToInt32(file[0]);

                    if (dir == "/") break;

                    var dirSplit = dir.Split("/").ToList();
                    dirSplit.RemoveAt(dirSplit.Count-1);
                    dir = string.Join("/",dirSplit);
                }
            }
        }

        int maxSpace = 70000000;
        int minUnused = 30000000;
        int currentUnused = maxSpace - directorySize["/"];
        int requiredSpace =  minUnused - currentUnused;

        int smallestSize = Int32.MaxValue;

        foreach(var item in directorySize)
        {
            if (requiredSpace < item.Value && item.Value < smallestSize){
                smallestSize = item.Value;
            }
        }

        Console.WriteLine($"Part Two: {smallestSize.ToString()}");
    }
    public static void Main() 
    {
        dynamic Lines = System.IO.File.ReadAllLines("input.txt");
        var input = new List<string>(Lines);

        // Part One
        PartOne(input);
        // Part Two
        PartTwo(input);
    }
}