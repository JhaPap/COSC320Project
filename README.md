# COSC320Project
COSC 320 Decision Tree

Decision Trees as a Machine Learning Algorithm and Their Application in Poker Strategy
 *
 * A decision tree is a popular machine learning algorithm that models decisions based on input data,
 * splitting data at each node according to specific criteria. Each node in the tree represents a
 * question or condition about an input feature, with branches corresponding to possible answers.
 * By traversing the tree from the root to a leaf node, the algorithm reaches a decision or prediction.
 *
 * In machine learning, decision trees are trained on labeled data. For example, in a classification
 * task, a decision tree learns to predict categories (like "spam" or "not spam") by finding the best
 * questions (features and values) to split the data at each node, optimizing for criteria like
 * information gain or Gini impurity. This process allows the tree to generalize patterns in data
 * for making accurate predictions on unseen examples. Decision trees are used in both classification
 * (discrete outputs) and regression (continuous outputs) tasks and serve as the foundation for
 * ensemble methods like Random Forests and Gradient Boosting.
 *
 * Application in Poker Strategy:
 *
 * In this poker code, a decision tree structure is applied to model poker decisions based on key
 * factors like hand strength, pot odds, and the number of players who called the big blind. While
 * this decision tree is not "learned" from data in the same way as in machine learning, it uses a
 * structured series of decision nodes to simulate how a machine learning model might evaluate a
 * poker hand. Each node in the tree represents a choice—whether to "raise," "call," or "fold"—and
 * branches are determined by game conditions. 
 *
 * Although the poker decision tree here is hard coded, it showcases the power of decision trees as
 * decision-making frameworks. If extended with a training component, the model could learn optimal
 * poker strategies from past game data, transforming it into a machine learning-based decision
 * tree.
