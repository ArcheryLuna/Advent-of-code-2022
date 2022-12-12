using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

public class Day7 {
    static void PartOne(dynamic input, dynamic grid) {
        // Create a new Counter
        int treesVisible = 0;

        treesVisible += (grid.Count * 2) + (grid[0].Count * 2) - 4 ;

        // Count trees
        for (int row = 1; row < grid.Count - 1; row++){
            for (int col = 1; col < grid[row].Count - 1; col++){
                int currentHeight = grid[row][col];

                bool isVisible = true;

                //left check
                for(int leftCol = col-1; leftCol >= 0; leftCol--){
                    if(grid[row][leftCol] >= currentHeight){
                        isVisible = false;
                        break;
                    }
                }
                if (isVisible){
                    treesVisible++;
                    continue;
                }
                isVisible = true;
                //right check
                for(int rightCol = col+1; rightCol < grid[row].Count; rightCol++){
                    if(grid[row][rightCol] >= currentHeight){
                        isVisible = false;
                        break;
                    }
                }
                if (isVisible){
                    treesVisible++;
                    continue;
                }
                isVisible = true;
                //up check
                for(int upRow = row-1; upRow >= 0; upRow--){
                    if(grid[upRow][col] >= currentHeight){
                        isVisible = false;
                        break;
                    }
                }
                if (isVisible){
                    treesVisible++;
                    continue;
                }
                isVisible = true;
                //down check
                for(int downRow = row+1; downRow < grid.Count; downRow++){
                    if(grid[downRow][col] >= currentHeight){
                        isVisible = false;
                        break;
                    }
                }
                if (isVisible){
                    treesVisible++;
                }
            }
        }
        // Print result
        Console.WriteLine($"Part One: {treesVisible}");
    }

    static void PartTwo(dynamic input, dynamic grid) {
        int bestScore = 0;

        for (int row = 1; row < grid.Count - 1; row++) {
            for (int col = 1; col < grid[row].Count - 1; col++) {

                int upScore = 0;
                int downScore = 0;
                int leftScore = 0;
                int rightScore = 0;

                int currentHeight = grid[row][col];

                //left check
                for(int leftCol = col-1; leftCol >= currentHeight; leftCol--){
                    leftScore++;
                    if(grid[row][leftCol] >= currentHeight){
                        break;
                    }
                }

                //right check
                for(int rightCol = col+1; rightCol < grid[row].Count; rightCol++){
                    rightScore++;
                    if(grid[row][rightCol] >= currentHeight){
                        break;
                    }
                }

                //up check
                for(int upRow = row-1; upRow >= 0; upRow--){
                    upScore++;
                    if(grid[upRow][col] >= currentHeight){
                        break;
                    }
                }

                //down check
                for(int downRow = row+1; downRow < grid.Count; downRow++){
                    downScore++;
                    if(grid[downRow][col] >= currentHeight){
                        break;
                    }
                }

                int senarioScore = upScore * downScore * leftScore * rightScore;

                if (senarioScore > bestScore){
                    bestScore = senarioScore;
                }
            }
        }
        Console.WriteLine($"Part Two: {bestScore}");
    }

    public static void Main() 
    {
        dynamic Lines = System.IO.File.ReadAllLines("input.txt");
        var input = new List<string>(Lines);

        var grid = new List<List<int>>();

        // Create grid
        foreach (var line in input) {
            var row = new List<int>();
            foreach (var c in line) {
                row.Add(int.Parse(c.ToString()));
            }
            grid.Add(row);
        }

        // Part One
        PartOne(input, grid);
        // Part Two
        PartTwo(input, grid);
    }
}