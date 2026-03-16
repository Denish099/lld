/*
its is a structural design pattern that allows us two incompatable interface to work
with each other . it acts as the bridge between the interfaces a client expects and the actual
interface of an existing class
*/

#include <iostream>
#include <string>

#define endl "\n"

using namespace std;

class PaymentGateway
{
public:
    virtual void pay(string orderId, double amount) = 0;
    virtual ~PaymentGateway() = default;
};

class PayU : public PaymentGateway
{
public:
    void pay(string orderId, double amount) override
    {
        cout << "payed" << amount << "via payu" << endl;
    }
};

// razorPay is the third party api so we cant directly use in our checkout service
class RazorpayApi
{
public:
    void makePayment(string invoiceId, double amountInRuppes)
    {
        cout << "payed" << amountInRuppes << "via razorPay" << endl;
    }
};
// so we are going to create a razorpay adapter so it can integrate with razorpay api
class RazorPayAdapter : public PaymentGateway
{
private:
    RazorpayApi *instance;

public:
    RazorPayAdapter()
    {
        this->instance = new RazorpayApi();
    }

    void pay(string orderId, double amount) override
    {
        instance->makePayment(orderId, amount);
    }
};
class CheckoutService
{
private:
    PaymentGateway *instance;

public:
    CheckoutService(PaymentGateway *instance)
    {
        this->instance = instance;
    }

    void checkout(string orderId, double amount)
    {
        instance->pay(orderId, amount);
    }
};

int main()
{
    CheckoutService *instance = new CheckoutService(new PayU());
    instance->checkout("denish", 500);

    CheckoutService *instance2 = new CheckoutService(new RazorPayAdapter());
    instance2->checkout("deis",500);

    return 0;
}