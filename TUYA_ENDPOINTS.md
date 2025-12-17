# Correct Tuya API Endpoints

## ❌ Wrong URLs (Don't Work):
- https://openapi-weeu.tuyaeu.com
- https://openapi.tuyaus.com

## ✅ Correct URLs:

### Europe (Your Data Center):
- **Main**: https://openapi.tuyaeu.com
- **Alternative**: https://openapi-eu.tuyaeu.com

### US (Alternative):
- https://openapi.tuyaus.com

### China:
- https://openapi.tuya.com

## Your Fixed Configuration:
```cpp
const char* endpoint = "https://openapi.tuyaeu.com";  // Europe
```

## Test the Endpoint:
```bash
curl -X GET "https://openapi.tuyaeu.com/v1.0/token?grant_type=1" \
  -H "client_id: mraudgsm5fs77tj8wmyf" \
  -H "secret: 4733aa38304f4ac5b235ae3984c137f9"
```

## If Still Not Working:
Try these alternatives in order:
1. https://openapi.tuyaeu.com
2. https://openapi-eu.tuyaeu.com  
3. https://openapi.tuyaus.com
