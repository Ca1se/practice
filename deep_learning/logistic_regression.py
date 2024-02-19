import torch
import random

num_examples = 1000
batch_size = 10
true_w = torch.tensor([-1.5, -2.0])
true_b = 3.0

def generate_test_data(true_w, true_b, num_examples):
    X = 2 * torch.rand((num_examples, 2))
    Z = torch.matmul(X, true_w.reshape((-1, 1))) + true_b
    Y = torch.zeros((num_examples, 1))
    for i in range(num_examples):
        if Z[i] >= 0:
            Y[i] = 1
    return X, Y.reshape((-1, 1))
test_features, test_labels = generate_test_data(true_w, true_b, num_examples)

def data_iter(features, labels, num_examples, batch_size):
    indices = [i for i in range(num_examples)]
    random.shuffle(indices)
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(indices[i: min(i + batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]

def loss(w, b, x, y):
    z = torch.matmul(x, w) + b
    return -y * z + torch.log(1.0 + torch.e**z)

def SGD(params, learning_rate, batch_size):
    with torch.no_grad():
        for param in params:
            param -= learning_rate * param.grad / batch_size
            param.grad.zero_()

num_epochs = 1000
learning_rate = 0.3
trainer = SGD

w = torch.normal(0.0, 1.0, (2, 1), requires_grad = True)
b = torch.zeros(1, requires_grad = True)

for epoch in range(num_epochs):
    for X, y in data_iter(test_features, test_labels, num_examples, batch_size):
        l = loss(w, b, X, y)
        l.sum().backward()
        trainer([w, b], learning_rate, batch_size)
    with torch.no_grad():
        training_l = loss(w, b, test_features, test_labels)
        print(f'epoch {epoch + 1}, loss: {float(training_l.mean())}')

print(w, b)
