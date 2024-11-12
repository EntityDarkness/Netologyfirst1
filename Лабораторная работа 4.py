import yaml
import json
from pprint import pprint

with open('input.yaml', 'r', encoding='utf-8') as f:
    temp = yaml.safe_load(f)

pprint(temp)

new_temp = json.dumps(temp, ensure_ascii=False, indent=3).encode('utf-8')
print(new_temp.decode())

with open('output.json', 'wb') as f:
    f.write(new_temp)