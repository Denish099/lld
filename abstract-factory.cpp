#include <iostream>
using namespace std;

class PaymentGateway {
public:
    virtual ~PaymentGateway() = default;

    virtual void processPayment(double amount) = 0;
};

class Invoice {
public:
    virtual ~Invoice() = default;

    virtual void generateInvoice() = 0;
};

class RazorpayGateway : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "Processing INR payment via Razorpay: " << amount << "\n";
    }
};

class PayUGateway : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "Processing INR payment via PayU: " << amount << "\n";
    }
};

class GSTInvoice : public Invoice {
public:
    void generateInvoice() override {
        cout << "Generating GST Invoice for India.\n";
    }
};

class PayPalGateway : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "Processing USD payment via PayPal: " << amount << "\n";
    }
};

class StripeGateway : public PaymentGateway {
public:
    void processPayment(double amount) override {
        cout << "Processing USD payment via Stripe: " << amount << "\n";
    }
};

class USInvoice : public Invoice {
public:
    void generateInvoice() override {
        cout << "Generating Invoice as per US norms.\n";
    }
};

class RegionFactory {
public:
    virtual ~RegionFactory() = default;

    virtual unique_ptr<PaymentGateway> createPaymentGateway(const string &gatewayType) = 0;

    virtual unique_ptr<Invoice> createInvoice() = 0;
};

class IndiaFactory : public RegionFactory {
public:
    unique_ptr<PaymentGateway> createPaymentGateway(const string &gatewayType) override {
        if (gatewayType == "razorpay") {
            return make_unique<RazorpayGateway>();
        }
        if (gatewayType == "payu") {
            return make_unique<PayUGateway>();
        }

        throw invalid_argument("Unsupported gateway for India: " + gatewayType);
    }

    unique_ptr<Invoice> createInvoice() override {
        return make_unique<GSTInvoice>();
    }
};

class USFactory : public RegionFactory {
public:
    unique_ptr<PaymentGateway> createPaymentGateway(const string &gatewayType) override {
        if (gatewayType == "paypal") {
            return make_unique<PayPalGateway>();
        }
        if (gatewayType == "stripe") {
            return make_unique<StripeGateway>();
        }

        throw invalid_argument("Unsupported gateway for US: " + gatewayType);
    }

    unique_ptr<Invoice> createInvoice() override {
        return make_unique<USInvoice>();
    }
};

class CheckoutService {
    unique_ptr<PaymentGateway> paymentGateway;
    unique_ptr<Invoice> invoice;

public:
    CheckoutService(RegionFactory &factory, const string &gatewayType) {
        paymentGateway = factory.createPaymentGateway(gatewayType);
        invoice = factory.createInvoice();
    }

    void completeOrder(double amount) {
        paymentGateway->processPayment(amount);
        invoice->generateInvoice();
    }
};

int main() {
    IndiaFactory indiaFactory;
    CheckoutService indiaCheckout(indiaFactory, "razorpay");
    indiaCheckout.completeOrder(1999.0);

    cout << "---\n";

    USFactory usFactory;
    CheckoutService usCheckout(usFactory, "paypal");
    usCheckout.completeOrder(49.99);

    return 0;
}