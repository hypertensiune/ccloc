import sys
import matplotlib.pyplot as plt
import json

time = []
th = []

counter = 1

with open(sys.argv[1]) as f:
    json_data = json.load(f)

    for result in json_data['results']:
        time.append(result['mean'])

        th.append(counter)

        counter += 1

fig, ax = plt.subplots(figsize=(18,11))

plt.barh(th, time)

for i, v in enumerate(time):
    plt.text(v, i + 0.8, str(v)[:5])

ax.set_xlabel("time in seconds")
ax.set_ylabel("threads")
ax.set_yticks(th, labels=th)

ax.set_title("Multi threaded performance")

plt.show()