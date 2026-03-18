#include <iostream>
#include <string>

using namespace std;

class PaymentService {
public:
    void makePayment(const string& accountId, double amount) {
        cout << "Payment of \u20B9" << amount << " successful for account " << accountId << "\n";
    }
};

class SeatReservationService {
public:
    void reserveSeat(const string& movieId, const string& seatNumber) {
        cout << "Seat " << seatNumber << " reserved for movie " << movieId << "\n";
    }
};

class NotificationService {
public:
    void sendBookingConfirmation(const string& userEmail) {
        cout << "Booking confirmation sent to " << userEmail << "\n";
    }
};

class LoyaltyPointsService {
public:
    void addPoints(const string& accountId, int points) {
        cout << points << " loyalty points added to account " << accountId << "\n";
    }
};

class TicketService {
public:
    void generateTicket(const string& movieId, const string& seatNumber) {
        cout << "Ticket generated for movie " << movieId << ", Seat: " << seatNumber << "\n";
    }
};

class MovieBookingFacade {
private:
    PaymentService paymentService;
    SeatReservationService seatReservationService;
    NotificationService notificationService;
    LoyaltyPointsService loyaltyPointsService;
    TicketService ticketService;

public:
    MovieBookingFacade() = default;

    void bookMovieTicket(
        const string& accountId,
        const string& movieId,
        const string& seatNumber,
        const string& userEmail,
        double amount
    ) {
        paymentService.makePayment(accountId, amount);

        seatReservationService.reserveSeat(movieId, seatNumber);

        ticketService.generateTicket(movieId, seatNumber);

        loyaltyPointsService.addPoints(accountId, 50);

        notificationService.sendBookingConfirmation(userEmail);

        cout << "Movie ticket booking completed successfully!" << "\n";
    }
};

int main() {
    MovieBookingFacade movieBookingFacade;

    movieBookingFacade.bookMovieTicket("user123", "movie456", "A10", "user@example.com", 500);

    return 0;
}