# ============================================
# 点餐终端系统 - 通信协议定义
# 传输方式: TCP Socket
# 数据格式: JSON (UTF-8 编码)
# 默认端口: 8888
# ============================================

## 一、协议概述

客户端与服务器之间通过 TCP Socket 进行通信，所有数据均使用 JSON 格式进行序列化。
每条消息为一个完整的 JSON 对象，通过 `type` 字段区分消息类型。

菜品图片通过 base64 编码嵌入 JSON 传输，客户端解码后显示。

---

## 二、客户端 → 服务器

### 2.1 请求菜单

```json
{
    "type": "get_menu"
}
```

### 2.2 提交订单

```json
{
    "type": "submit_order",
    "order": {
        "table_no": "A01",
        "people_count": 3,
        "total_price": 89.00,
        "create_time": "2026-05-09 11:30:00",
        "items": [
            {
                "dish_id": 1,
                "dish_name": "宫保鸡丁",
                "price": 28.00,
                "count": 2,
                "subtotal": 56.00
            }
        ]
    }
}
```

---

## 三、服务器 → 客户端

### 3.1 菜单数据响应（含图片）

```json
{
    "type": "menu_data",
    "data": [
        {
            "dish_id": 1,
            "dish_name": "宫保鸡丁",
            "price": 28.00,
            "stock": 50,
            "description": "经典川菜，花生鸡丁",
            "status": 1,
            "image_data": "iVBORw0KGgoAAAANSUhEUgAA..."
        },
        {
            "dish_id": 2,
            "dish_name": "鱼香肉丝",
            "price": 26.00,
            "stock": 40,
            "description": "甜酸微辣，下饭首选",
            "status": 1,
            "image_data": ""
        }
    ]
}
```

> `image_data` 字段为 base64 编码的图片数据，无图片时为空字符串。

### 3.2 订单结果响应

成功：
```json
{
    "type": "order_result",
    "success": true,
    "order_id": 1,
    "msg": "订单保存成功，订单号：1"
}
```

失败：
```json
{
    "type": "order_result",
    "success": false,
    "order_id": -1,
    "msg": "订单保存失败"
}
```

---

## 四、字段说明

| 字段 | 类型 | 说明 |
|------|------|------|
| type | string | 消息类型：get_menu / menu_data / submit_order / order_result |
| data | array | 菜单数据数组 |
| order | object | 订单对象 |
| success | bool | 操作是否成功 |
| order_id | int | 订单编号（成功时为正数，失败时为 -1） |
| msg | string | 结果描述信息 |
| dish_id | int | 菜品编号 |
| dish_name | string | 菜品名称 |
| price | double | 菜品单价 |
| stock | int | 菜品库存 |
| count | int | 购买数量 |
| subtotal | double | 小计金额 |
| table_no | string | 餐桌号 |
| people_count | int | 就餐人数 |
| total_price | double | 订单总价 |
| create_time | string | 下单时间，格式 yyyy-MM-dd hh:mm:ss |
| status | int | 状态：1=上架/0=下架（菜单），0=已下单/1=已完成/2=已取消（订单） |
| image_data | string | 菜品图片 base64 编码数据，无图片时为空字符串 |
| image_path | string | 菜品图片服务器本地路径（仅服务器端使用，不发送给客户端） |
