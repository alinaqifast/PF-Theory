/* 
Class: bcs-1c
Roll: 25K-0989
Name: Ali Naqi 

Question 1
 */

#include <stdio.h>
#include <math.h>

/* Calculate repayment recursively.
 * loan: remaining loan
 * interestRate: yearly interest in percent (e.g., 5 for 5%)
 * years: years remaining
 * installment: fixed yearly installment paid at start of each year
 * extraPayment: extra payment applied each year (can be 0)
 *
 * Prints Year X: Remaining loan = Y each year.
 * Returns total amount paid over the given years (installments + interest + extras).
 */
double calculateRepayment(double loan, double interestRate, int years, double installment, double extraPayment, int yearCounter) {
    if (loan <= 0.0 || years <= 0) {
        /* base case: loan fully repaid or no years left */
        if (loan < 0.0) loan = 0.0;
        return 0.0;
    }

    /* pay installment + extra at the start of the year */
    double payment = installment + extraPayment;
    if (payment > loan) payment = loan; /* can't pay more than remaining loan principal */

    loan -= payment;

    /* apply interest to remaining loan */
    loan += loan * (interestRate / 100.0);

    printf("Year %d: Remaining loan = %.2f\n", yearCounter, loan);

    /* recursive call for remaining years */
    double futurePaid = calculateRepayment(loan, interestRate, years - 1, installment, extraPayment, yearCounter + 1);

    return payment + futurePaid;
}

/* Example tracing for loan = 100000, interest = 5%, years = 3.
 * We'll choose fixed installment = principal / years (simple).
 */
int main(void) {
    double loan = 100000.0;
    double rate = 5.0;
    int years = 3;
    double installment = loan / years; /* simple fixed installment choice */
    double extraPayment = 0.0; /* no extra payments in base trace */

    printf("Tracing repayment for loan=%.2f rate=%.2f%% years=%d\n", loan, rate, years);
    printf("Using fixed installment = %.2f per year (simple choice)\n\n", installment);

    /* Print initial state */
    printf("Year 0: Remaining loan = %.2f\n", loan);

    double totalPaid = calculateRepayment(loan, rate, years, installment, extraPayment, 1);

    printf("\nTotal paid over %d years = %.2f\n", years, totalPaid);

    /* Short explanation:
     * Recursion helps by carrying the updated loan state into the next call.
     * Each call handles one year, prints state, and asks the next call to handle the next year.
     */

    /* Small demo of extension: extra yearly payments example */
    printf("\nDemo with extra yearly payment of 5000 added each year:\n");
    printf("Year 0: Remaining loan = %.2f\n", 100000.0);
    totalPaid = calculateRepayment(100000.0, rate, years, installment, 5000.0, 1);
    printf("Total paid (with extra 5000/year) = %.2f\n", totalPaid);

    return 0;
}
