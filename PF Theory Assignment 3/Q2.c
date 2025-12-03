/* 
Class: bcs-1c
Roll: 25K-0989
Name: Ali Naqi 

Question 2
 */

#include <stdio.h>

/* Recursive fuel calculator
 * fuel: current fuel
 * consumption: fixed fuel used at each planet stop
 * recharge: fuel regained in special gravitational zones (if any)
 * solarBonus: extra fuel added after every 4th planet (i.e., planet%4 == 0)
 * planet: current planet index (1-based)
 * totalPlanets: total stops to visit
 *
 * Returns 1 if mission can complete remaining planets, 0 if fuel exhausted early.
 */


int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (fuel <= 0) {
        printf("Planet %d: Fuel Remaining = 0 (exhausted)\n", planet);
        return 0; /* failed */
    }
    if (planet > totalPlanets) {
        /* visited all planets already; success */
        return 1;
    }

    /* consume fuel for this planetary stop */
    fuel -= consumption;
    if (fuel < 0) fuel = 0;

    /* optionally get gravitational recharge on some planets:
     * Here we model a simple rule: every planet with (planet % 3 == 0) gives a gravitational assist..
     */
    if (planet % 3 == 0) {
        fuel += recharge;
    }

    /* every 4th planetary stop, solar panels give a bonus */
    if (planet % 4 == 0) {
        fuel += solarBonus;
    }

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    if (fuel <= 0) return 0; /* exhausted after this stop */

    /* recursive call for next planet */
    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main(void) {
    int initFuel = 1000;
    int consumption = 120; /* fuel used at each stop */
    int recharge = 50;     /* gravitational assist recharge */
    int solarBonus = 200;  /* bonus after every 4th stop */
    int totalPlanets = 10;

    printf("Starting fuel: %d\n", initFuel);
    printf("Simulating %d planetary stops\n\n", totalPlanets);

    int success = calculateFuel(initFuel, consumption, recharge, solarBonus, 1, totalPlanets);

    if (success) printf("\nSpacecraft completed the journey.\n");
    else printf("\nSpacecraft failed: fuel exhausted before completing the journey.\n");

    return 0;
}
