package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

// exponential growth formula
// y = a(1+r)^t
// a: initial value, r: rate of change
// t: time

func SmartFishSim(fish []int, days int, lifespan int, respawnAge int) int {
	fishPerDay := make([]int, lifespan)
	for _, f := range fish {
		fishPerDay[f]++
	}
	fmt.Printf("\nInitial fish state: %v", fishPerDay)

	last := len(fishPerDay) - 1
	secondLast := last - 1

	for i := 0; i < days; i++ {
		fmt.Printf("\nDay %d ", i)
		newFish := 0
		for j := 0; j < last; j++ {
			if j == 0 && fishPerDay[j] != 0 {
				newFish = fishPerDay[j]
			}
			if j <= secondLast {
				fishPerDay[j] = fishPerDay[j+1]
			}
		}
		fishPerDay[respawnAge] += newFish
		fishPerDay[last] = newFish
		fmt.Printf("\nEnd of day status: %v", fishPerDay)
	}

	sum := 0
	for _, fish := range fishPerDay {
		sum += fish
	}
	return sum
}

func DumbFishSim(fish []int, days int) int {
	fmt.Printf("\nDay 0: %v", fish)
	for d := 1; d <= days; d++ {
		for i := 0; i < len(fish); i++ {
			fish[i] = fish[i] - 1
			if fish[i] == -1 {
				fish[i] = 6
				fish = append(fish, 9)
			}
		}
		fmt.Printf("\nDay %d, len=%d", d, len(fish))
	}
	return len(fish)
}

func main() {
	file, err := os.Open("Y2021D06_input.txt")
	if err != nil {
		log.Fatal(err)
	}

	scanner := bufio.NewScanner(file)
	var tokens []string
	// effectively a list of lines (strings)
	for scanner.Scan() {
		tokens = append(tokens, scanner.Text())
	}
	// first element of tokens is literally whole input
	split := strings.Split(tokens[0], ",")
	var fish []int
	for _, s := range split {
		num, err := strconv.Atoi(s)
		if err != nil {
			log.Fatal(err)
		}
		fish = append(fish, num)
	}

	sum := DumbFishSim(fish, 256)
	// sum := SmartFishSim(fish, 256, 9, 6) // fish, days, lifespan, respawn Age
	fmt.Printf("\n\nTotal fish population is %d", sum)
}
