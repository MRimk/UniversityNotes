<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

## ML Security

### Machine learning

#### ML Taxonomy

3 areas:

- supervised learning (labeled data, direct feedback, predict outcome/future, example - estimate house price) **Most used and wehere security has been mostly studied**. silo.com lost a lot of money by evaluating houses using ML model; or HFT
- unsupervised learning (decision process, reward system, learn series of actions, example: learning to play a game)
- reinforcement learning (no labels, no feedbacks, "find hidden structures", example: customer segmentation)

#### Supervised learning

A lot of data points with labels.
Then the features are extracted.
Then the weights are applied during training to get a model.

And then using a sample of data and extracted features, they can be passed through the model to get the label back.

#### Adversary goals

- give fake input samples (if there is a feedback loop); disturbing the model to make it misclassify
- violate property - steal the model
- by querying, could try to extract information that the model has
- violate privacy - steal information or recovering samples
- fool the user - Alter the output of the model

#### ML under adversarial conditions

Confidentiality and privacy:
Confidentiality of the model itself (E.g. intellectual property or it was expensive to train the model)
Privacy of the training or test data (e.g. medical records)

Integrity and availability:
Integrity of the predicitons (wrt expected outcome)
Availability of the system deploying machine learning

**Opaque-box attacks**:
model arch and parameters unknown, can only interact blindly with the model

**Grey-box attacks**:
model arch is known, parameters unknown
Can only interact with the model but has informatio nabout the type of model

**Clear-box attacks**:
known arch and parameters
Can replicate the model and use the model's unternal parameters in the attack

Opaque-box attacks -> Grey-box attacks -> Clear-box attacks (higher success rate, but more threatening is the opposite way)

### Model stealing

#### ML as a service

it's not usually run on local, but on cloud

1. Cloud (pre-)trains a classifier using their own data
2. Make this classifier available as a service for users to query
3. the user makes a query "given their profile (photos, posts, metadata) what per has this fb user?"

#### Adversary for model stealing

so that they don't have to pay for each query

Confidentiality of the model itself (e.g. intellectual property)

Good ML models require investment:

- collecting data takes time and money
- training infrastructure is expensive

goal: "steal" the expensive model by observing its outputs with lower cost than obtaining the data and training

#### Stealing a linear model

Assuming the adv knows the model is a linear arch (grey-box model)
and assuming x is two dimensional

Adversary's goald steal parameters w, b

For n-dimentional x, we need n+1 queries

#### Stealing non-linear model

Assuming the adv knows the model arch (grey-box model)

Goal: steal parameters w

Do **retraining attack** - observe many queries X=(x,f(x)) and fit the model on X like on any other training data

Takes many queries, For a nn with 2K parameters, need 11K queries to get 99.9% similarity.
More recent work has reduced these numbers

Given (oracle) query access to a nn, learned through stochastic gradient descent, we can extract a functionally equivalent model - locaktion of the critical hyperplanes almost completely determines the nn

**Implication of this attack**:
assumption of the field of secure inference - observing the output of a nn does not reveal the weights <- this is false, and therefore the field os secure inference will need to develop new techniques to protect models

#### Preventing model stealing

first attack 2016, first defences - 2017

Output perturbation - add noise to the probabilities output by the model to hinder reconstruction but not accuracy

Detect suspicious queries - pattern matching technique
Identify deviations from expected on distribution of successive queries from a client

#### Takeaways on model stealing

- Many models are susceptible to stealing (recovering parameters or at minimum extracting sufficient training data)
- Complex topic, lots of ongoing research
- Crucial issue for MLaaS
- Many problems, some solutions
- Very young field

### Privacy challenges in ML

There's always some sort of leakage in models

Privacy-preserving Machine Learning is an active research area

#### Privacy risks

Training: information leaks about data used for training (membership inference attacks)

Testing: Testing data (or the result) might be sensitive in MLaaS

Tay - MS chatbot which was supposed to have a personality of a teenage person, and it took a day to make it very racist.

#### Privacy risks of ML

**Before ML era**
user's data -> services
Privacy threats: colletion of sensitive personal data, re-identification, inference attacks

Now:
user's data -> ML -> services
Do trained models leak sensiteve data?
Can we train good privacy-preserving models?

#### Typical task - classification

Training set -> ML model
Query -> model -> prediction

**Membership inference**: figure out if a certain target data was in the "sensitive" dataset?
E.g. more similar to "reference" dataset or the "summary statistics" (this would show that it is more in the sensitive data)

**Assumption**: we don't know the model's parameters
For ML we don't know the model's parameters, but we can classify by inputs in the training set and inputs not in it.

The attacker can train a similar model to recognize the differences between the two distributions **without knowing the parameters of the actual model**. The idea of attacker - leverage sufficient public data to train the model and then compare.

**Assumption**: we don't know the parameters and we don't have access to training data

We train shadow models with the distributions, and with them we train the attack model to predict if an input wasa member of the training set (in) or a non-member (out)

**Assumption**: we have no knowledge of the underlying distribution of training data

Use data synthesis to create the data for us.
We train on random data and adjust the random data accordingly, and then retrain the model.

#### Why do these attacks work?

Originally the training the the companies do, it **overfits**, and then the attacker can retrieve a large amout of the infomation.

Privacy and utility are not in conflict: overfitting is the common enemy (overfitted models leak training data, and overfitted models lack preditctive power)
Need generalizability and accuracy

### Altering the Output

**Adversarial examples** - inputs that will make ML fail.
working definition:
Inputs to a model that an attacker has designed to cause the model to make a mistake

e.g. Panda image + .007 x Adversarial Perturbation = Panda gets identified as Gibbon (slightly change the saturation)

**Independent and identically distributed (IID) assumptions no longer hold**

1. Identical: inputs are intentionally manipulated to not belong to the training distribution
2. Independence: inputs are no longer drawn independently; the attacker may sample from a single input repeatedly.

#### Adversarial example problem

ML training:
Objective: find model parameters that minimize empirical loss

x, y in training data X with some loss function which takes x, y and parameters w
These weights are trained using gradient descent to **minimize** loss

Adversarial example problem
**goal**: find a perturbation that **maximizes** loss, that pushes the sample in another feature space
find maximized loss such that the, that pushes the sample in another feature space

Similarity relation is often represented as adversarial cost constraint.

Constraint on perturbation norm assumes that similar images are close in e.g. Euclidean distance (this is not always true)
For example, similarity could be defined as small affine transformation, and then gets misclassified.
Feature extraction could be wrong because of the transformation.

Attacks don't have to be imperceptible - sometimes image can be altered even it is seen and that makes the model misclassify.

How to solve optimization problem where there are limited pixel changes: define the problem as gradient descent attack, where the direction is taken towards maximum loss, and project to meet constraint.

#### Transferability property

Adversarial examples have a **transferability** property - samples crafted to mislead a model A are likely to mislead a model B

In the most extreme case, it is possible to construct a single perturbation that will fool a model when added to any image. -> Attackers need minimal resources to attack the system

#### Defending against adversarial examples

Defending in general is very hard. - you cannot add noise to defend
Can only defend against a particular threat model (e.g. perturbations up to epsilon norm), and normally no guarantees

Sandard way is **adversarial training** (based on _robust optimization_). It means training on simulated adversarial examples.

#### Preventing adversarial examples

Certified defenses: ensure that no example can exist inside a ball with radius the norm used for the perturbation (train multiple models and have the answer that the models have to agree on)

Detect suspicious queries: identify deviations from expected on distribution of successive queries form a client

(unclear whether they are really effective)

**Attackers are not restricted to computer vision**

### Biases and Fallacies

#### Base rate fallacy / Prosecutor's fallacy

We assume equal distribution of cases, if they are not we falsely interpret results

AI performance metrics - example of hate speech detection - sets are not the same

TP: prediction prediction hate speech in hate speech
FN: prediction prediciton not hate speech in hate speech
TN: prediction not hate speech in not hate speech
FP: prediction hate speech - in not hate speech

#### Distributional shift

Because of the size of the training set certain classes could be classified less accurately

#### Transparency

Classification Task: Should we send a patient with Bronchitis home?
Rule-Based Learning
If x, then y
Human readable rules: causation is intrinsic

Machine Learning
Better accuracy
Not directly possible to understand why a decision is made

#### Bias reinforcement

it is a bigger problem because bias gets completely implemented in reinforcement learning

**Bias**
Statistical bias: difference between an estimator expected value and the true value
Very limited! Nothing about errors, nothing about distributional shift

Group fairness: outcome should not differ between demographic groups

Individual fairness: similar? individuals should be treated similarly?
