reward_t = torch.tensor(reward_list, dtype=torch.float)
means = reward_t.unfold(0, 100, 1).mean(1).view(-1)
means = torch.cat((torch.zeros(99), means))

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(25, 5))
ax1.set_title('Reward per episode')
ax1.set_xlabel('Episode')
ax1.set_ylabel('Reward')
ax1.plot(reward_list, label='Reward for 1 episode')
ax1.plot(means, label='Average reward for 100 episodes')
ax1.legend(loc='best')

ax2.set_title('Loss per episode')
ax2.set_xlabel('Episode')
ax2.set_ylabel('Loss')
ax2.plot(losses_list)
plt.show()

plt.savefig('Reward_n_loss.png', dpi=300)