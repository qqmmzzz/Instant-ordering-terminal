const {
  Document, Packer, Paragraph, TextRun, Table, TableRow, TableCell,
  Header, Footer, PageNumber, AlignmentType, HeadingLevel, WidthType,
  BorderStyle, ShadingType, PageBreak
} = require("docx");
const fs = require("fs");

// Color palette - GO-1 Graphite Orange (tech proposal style)
const P = {
  primary: "1A2330",
  body: "000000",
  secondary: "607080",
  accent: "D4875A",
  surface: "F8F0EB",
  cover: {
    titleColor: "FFFFFF",
    subtitleColor: "B0B8C0",
    metaColor: "90989F",
    footerColor: "687078",
  },
  table: {
    headerBg: "D4875A",
    headerText: "FFFFFF",
    accentLine: "D4875A",
    innerLine: "DDD0C8",
    surface: "F8F0EB",
  }
};

const NB = { style: BorderStyle.NONE, size: 0, color: "FFFFFF" };
const allNoBorders = { top: NB, bottom: NB, left: NB, right: NB, insideHorizontal: NB, insideVertical: NB };

// Helper functions
function heading1(text) {
  return new Paragraph({
    heading: HeadingLevel.HEADING_1,
    spacing: { before: 360, after: 160 },
    children: [new TextRun({ text, bold: true, size: 32, font: { ascii: "Calibri", eastAsia: "SimHei" }, color: P.primary })]
  });
}

function heading2(text) {
  return new Paragraph({
    heading: HeadingLevel.HEADING_2,
    spacing: { before: 280, after: 120 },
    children: [new TextRun({ text, bold: true, size: 28, font: { ascii: "Calibri", eastAsia: "SimHei" }, color: P.primary })]
  });
}

function heading3(text) {
  return new Paragraph({
    heading: HeadingLevel.HEADING_3,
    spacing: { before: 200, after: 100 },
    children: [new TextRun({ text, bold: true, size: 24, font: { ascii: "Calibri", eastAsia: "SimHei" }, color: P.primary })]
  });
}

function bodyPara(text) {
  return new Paragraph({
    alignment: AlignmentType.JUSTIFIED,
    indent: { firstLine: 480 },
    spacing: { line: 312, after: 80 },
    children: [new TextRun({ text, size: 24, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" }, color: P.body })]
  });
}

function bodyParaNoIndent(text) {
  return new Paragraph({
    spacing: { line: 312, after: 80 },
    children: [new TextRun({ text, size: 24, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" }, color: P.body })]
  });
}

function codeBlock(lines) {
  return lines.map(line => new Paragraph({
    spacing: { line: 276, after: 0 },
    indent: { left: 480 },
    children: [new TextRun({ text: line, size: 20, font: { ascii: "Consolas", eastAsia: "Microsoft YaHei" }, color: "2C3E50" })]
  }));
}

function makeHeaderCell(text, widthPct) {
  return new TableCell({
    width: { size: widthPct, type: WidthType.PERCENTAGE },
    shading: { type: ShadingType.CLEAR, fill: P.table.headerBg },
    margins: { top: 60, bottom: 60, left: 120, right: 120 },
    children: [new Paragraph({
      alignment: AlignmentType.CENTER,
      children: [new TextRun({ text, bold: true, size: 21, color: P.table.headerText, font: { ascii: "Calibri", eastAsia: "SimHei" } })]
    })]
  });
}

function makeDataCell(text, widthPct, isAlt) {
  return new TableCell({
    width: { size: widthPct, type: WidthType.PERCENTAGE },
    shading: isAlt ? { type: ShadingType.CLEAR, fill: P.surface } : undefined,
    margins: { top: 50, bottom: 50, left: 120, right: 120 },
    children: [new Paragraph({
      children: [new TextRun({ text, size: 21, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" }, color: P.body })]
    })]
  });
}

function makeTable(headers, rows, colWidths) {
  const tableRows = [];
  // Header row
  tableRows.push(new TableRow({
    tableHeader: true,
    cantSplit: true,
    children: headers.map((h, i) => makeHeaderCell(h, colWidths[i]))
  }));
  // Data rows
  rows.forEach((row, ri) => {
    tableRows.push(new TableRow({
      cantSplit: true,
      children: row.map((cell, ci) => makeDataCell(cell, colWidths[ci], ri % 2 === 0))
    }));
  });

  return new Table({
    width: { size: 100, type: WidthType.PERCENTAGE },
    borders: {
      top: { style: BorderStyle.SINGLE, size: 2, color: P.table.accentLine },
      bottom: { style: BorderStyle.SINGLE, size: 2, color: P.table.accentLine },
      left: { style: BorderStyle.NONE },
      right: { style: BorderStyle.NONE },
      insideHorizontal: { style: BorderStyle.SINGLE, size: 1, color: P.table.innerLine },
      insideVertical: { style: BorderStyle.NONE },
    },
    rows: tableRows,
  });
}

// ====== Build Cover Section ======
function buildCover() {
  const bg = "1A2330";
  return {
    properties: {
      page: {
        size: { width: 11906, height: 16838 },
        margin: { top: 0, bottom: 0, left: 0, right: 0 },
      },
    },
    children: [
      new Table({
        width: { size: 100, type: WidthType.PERCENTAGE },
        borders: allNoBorders,
        rows: [new TableRow({
          height: { value: 16838, rule: "exact" },
          children: [new TableCell({
            width: { size: 100, type: WidthType.PERCENTAGE },
            shading: { type: ShadingType.CLEAR, fill: bg },
            verticalAlign: "top",
            borders: allNoBorders,
            children: [
              new Paragraph({ spacing: { before: 4200 }, children: [] }),
              new Paragraph({
                alignment: AlignmentType.CENTER,
                spacing: { line: 828, lineRule: "atLeast" },
                children: [new TextRun({ text: "Qt\u70b9\u9910\u7ec8\u7aef\u7cfb\u7edf", size: 72, bold: true, color: P.cover.titleColor, font: { ascii: "Calibri", eastAsia: "SimHei" } })]
              }),
              new Paragraph({
                alignment: AlignmentType.CENTER,
                spacing: { before: 200, line: 460, lineRule: "atLeast" },
                children: [new TextRun({ text: "\u9879\u76ee\u8bbe\u8ba1\u6587\u6863", size: 36, color: P.cover.subtitleColor, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" } })]
              }),
              new Paragraph({
                alignment: AlignmentType.CENTER,
                spacing: { before: 600 },
                children: [new TextRun({ text: "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500", size: 20, color: P.accent })]
              }),
              new Paragraph({
                alignment: AlignmentType.CENTER,
                spacing: { before: 400, line: 400 },
                children: [new TextRun({ text: "\u96be\u5ea6\u7b49\u7ea7\uff1a\u4e8c\u7ea7  |  \u5f00\u53d1\u5468\u671f\uff1a3\u5929", size: 22, color: P.cover.metaColor, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" } })]
              }),
              new Paragraph({
                alignment: AlignmentType.CENTER,
                spacing: { before: 120 },
                children: [new TextRun({ text: "\u6280\u672f\u6808\uff1aQt 5 / C++ / SQLite / TCP Socket / JSON", size: 22, color: P.cover.metaColor, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" } })]
              }),
              new Paragraph({
                alignment: AlignmentType.CENTER,
                spacing: { before: 120 },
                children: [new TextRun({ text: "\u6587\u6863\u7248\u672c\uff1aV1.0  |  \u65e5\u671f\uff1a2026-05-09", size: 22, color: P.cover.metaColor, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" } })]
              }),
            ]
          })]
        })]
      })
    ]
  };
}

// ====== Build Body Section ======
function buildBody() {
  const children = [];

  // ===== 1. 项目概述 =====
  children.push(heading1("1  \u9879\u76ee\u6982\u8ff0"));
  children.push(bodyPara("\u672c\u9879\u76ee\u662f\u4e00\u4e2a\u57fa\u4e8e Qt \u6846\u67b6\u7684 C/S \u67b6\u6784\u70b9\u9910\u7ec8\u7aef\u7cfb\u7edf\uff0c\u91c7\u7528\u5ba2\u6237\u7aef/\u670d\u52a1\u5668\u7aef\u53cc\u7aef\u8bbe\u8ba1\u6a21\u5f0f\u3002\u5ba2\u6237\u7aef\u63d0\u4f9b\u53ef\u89c6\u5316\u83dc\u5355\u6d4f\u89c8\u3001\u8d2d\u7269\u8f66\u7ba1\u7406\u3001\u8ba2\u5355\u63d0\u4ea4\u7b49\u529f\u80fd\uff0c\u670d\u52a1\u5668\u7aef\u8d1f\u8d23\u83dc\u5355\u6570\u636e\u7ba1\u7406\u3001\u8ba2\u5355\u5904\u7406\u4e0e\u5b58\u50a8\u3002\u53cc\u65b9\u901a\u8fc7 TCP Socket \u8fdb\u884c\u7f51\u7edc\u901a\u4fe1\uff0c\u4f7f\u7528 JSON \u683c\u5f0f\u8fdb\u884c\u6570\u636e\u4ea4\u6362\uff0c\u6570\u636e\u5e93\u91c7\u7528 SQLite \u8f7b\u91cf\u7ea7\u65b9\u6848\u3002\u7cfb\u7edf\u652f\u6301\u591a\u5ba2\u6237\u7aef\u540c\u65f6\u8fde\u63a5\uff0c\u5177\u5907\u5b9e\u65f6\u65f6\u949f\u663e\u793a\u3001\u8ba2\u5355\u4e8b\u52a1\u5904\u7406\u7b49\u7279\u6027\u3002"));
  children.push(bodyPara("\u672c\u6587\u6863\u8be6\u7ec6\u63cf\u8ff0\u4e86\u7cfb\u7edf\u7684\u6574\u4f53\u67b6\u6784\u8bbe\u8ba1\u3001\u6570\u636e\u5e93\u8bbe\u8ba1\u3001\u901a\u4fe1\u534f\u8bae\u5b9a\u4e49\u3001\u7c7b\u8bbe\u8ba1\u4e0e\u63a5\u53e3\u5b9a\u4e49\u3001\u754c\u9762\u5e03\u5c40\u8bbe\u8ba1\u4ee5\u53ca\u5173\u952e\u4ee3\u7801\u5b9e\u73b0\u7ec6\u8282\uff0c\u4e3a\u5f00\u53d1\u4eba\u5458\u63d0\u4f9b\u5b8c\u6574\u7684\u5b9e\u73b0\u6307\u5357\u3002\u9879\u76ee\u96be\u5ea6\u7b49\u7ea7\u4e3a\u4e8c\u7ea7\uff0c\u9884\u8ba1\u5f00\u53d1\u5468\u671f\u4e3a3\u5929\uff0c\u6db5\u76d6\u4e86 Qt \u7f51\u7edc\u7f16\u7a0b\u3001\u6570\u636e\u5e93\u64cd\u4f5c\u3001\u81ea\u5b9a\u4e49\u63a7\u4ef6\u3001\u4e8b\u52a1\u5904\u7406\u7b49\u6838\u5fc3\u6280\u672f\u70b9\u3002"));

  // ===== 2. 系统架构设计 =====
  children.push(heading1("2  \u7cfb\u7edf\u67b6\u6784\u8bbe\u8ba1"));
  children.push(heading2("2.1  \u6574\u4f53\u67b6\u6784"));
  children.push(bodyPara("\u7cfb\u7edf\u91c7\u7528\u7ecf\u5178\u7684\u5ba2\u6237\u7aef/\u670d\u52a1\u5668\uff08C/S\uff09\u4e24\u5c42\u67b6\u6784\uff0c\u5ba2\u6237\u7aef\u548c\u670d\u52a1\u5668\u7aef\u5206\u522b\u4f5c\u4e3a\u72ec\u7acb\u7684 Qt \u5de5\u7a0b\u8fd0\u884c\u3002\u670d\u52a1\u5668\u7aef\u542f\u52a8\u540e\u76d1\u542c\u6307\u5b9a\u7aef\u53e3\uff08\u9ed8\u8ba4 8888\uff09\uff0c\u7b49\u5f85\u5ba2\u6237\u7aef\u8fde\u63a5\uff1b\u5ba2\u6237\u7aef\u4e3b\u52a8\u8fde\u63a5\u670d\u52a1\u5668\u540e\uff0c\u53ef\u4ee5\u83b7\u53d6\u83dc\u5355\u3001\u63d0\u4ea4\u8ba2\u5355\u3002\u670d\u52a1\u5668\u7aef\u76f4\u63a5\u64cd\u4f5c SQLite \u6570\u636e\u5e93\uff0c\u5ba2\u6237\u7aef\u4e0d\u76f4\u63a5\u8bbf\u95ee\u6570\u636e\u5e93\uff0c\u6240\u6709\u6570\u636e\u64cd\u4f5c\u5747\u901a\u8fc7\u7f51\u7edc\u8bf7\u6c42\u5b8c\u6210\u3002\u8fd9\u79cd\u67b6\u6784\u4fdd\u8bc1\u4e86\u6570\u636e\u5b89\u5168\u6027\u548c\u7cfb\u7edf\u53ef\u6269\u5c55\u6027\u3002"));

  children.push(heading2("2.2  \u6280\u672f\u6808\u9009\u578b"));
  children.push(makeTable(
    ["\u6280\u672f\u7ec4\u4ef6", "\u9009\u578b", "\u8bf4\u660e"],
    [
      ["\u5f00\u53d1\u6846\u67b6", "Qt 5.x", "\u8de8\u5e73\u53f0 C++ GUI \u6846\u67b6\uff0c\u63d0\u4f9b\u4e30\u5bcc\u7684\u63a7\u4ef6\u548c\u7f51\u7edc\u6a21\u5757"],
      ["\u7f16\u7a0b\u8bed\u8a00", "C++17", "\u73b0\u4ee3 C++ \u6807\u51c6\uff0c\u652f\u6301\u667a\u80fd\u6307\u9488\u3001lambda \u7b49\u7279\u6027"],
      ["\u7f51\u7edc\u901a\u4fe1", "QTcpServer / QTcpSocket", "Qt \u5185\u7f6e TCP \u7f51\u7edc\u6a21\u5757\uff0c\u4e8b\u4ef6\u9a71\u52a8"],
      ["\u6570\u636e\u5e8f\u5217\u5316", "QJsonDocument / QJsonObject", "JSON \u683c\u5f0f\u8f7b\u91cf\u7ea7\u6570\u636e\u4ea4\u6362"],
      ["\u6570\u636e\u5e93", "SQLite (QSQLITE)", "\u65e0\u9700\u5b89\u88c5\u7684\u8f7b\u91cf\u7ea7\u5d4c\u5165\u5f0f\u6570\u636e\u5e93"],
      ["\u5b9a\u65f6\u5668", "QTimer", "\u5b9e\u73b0\u5b9e\u65f6\u65f6\u949f\u663e\u793a\u529f\u80fd"],
      ["\u754c\u9762\u8bbe\u8ba1", "Qt Designer (.ui)", "\u53ef\u89c6\u5316\u754c\u9762\u8bbe\u8ba1\uff0c\u652f\u6301\u5e03\u5c40\u7ba1\u7406"],
    ],
    [25, 30, 45]
  ));

  children.push(heading2("2.3  \u9879\u76ee\u76ee\u5f55\u7ed3\u6784"));
  children.push(...codeBlock([
    "OrderSystem/",
    "\u251c\u2500\u2500 database/",
    "\u2502   \u2514\u2500\u2500 init.sql              \u6570\u636e\u5e93\u521d\u59cb\u5316\u811a\u672c",
    "\u251c\u2500\u2500 Server/                    \u670d\u52a1\u5668\u7aef\u5de5\u7a0b",
    "\u2502   \u251c\u2500\u2500 Server.pro           \u9879\u76ee\u914d\u7f6e\u6587\u4ef6",
    "\u2502   \u251c\u2500\u2500 main.cpp             \u7a0b\u5e8f\u5165\u53e3",
    "\u2502   \u251c\u2500\u2500 serverwidget.h/cpp   \u670d\u52a1\u5668\u4e3b\u754c\u9762\u7c7b",
    "\u2502   \u251c\u2500\u2500 serverwidget.ui      \u754c\u9762\u5e03\u5c40\u6587\u4ef6",
    "\u2502   \u251c\u2500\u2500 mytcpserver.h/cpp    TCP\u670d\u52a1\u5668\u7c7b",
    "\u2502   \u251c\u2500\u2500 dbmanager.h/cpp      \u6570\u636e\u5e93\u7ba1\u7406\u7c7b",
    "\u2502   \u2514\u2500\u2500 ...",
    "\u251c\u2500\u2500 Client/                    \u5ba2\u6237\u7aef\u5de5\u7a0b",
    "\u2502   \u251c\u2500\u2500 Client.pro           \u9879\u76ee\u914d\u7f6e\u6587\u4ef6",
    "\u2502   \u251c\u2500\u2500 main.cpp             \u7a0b\u5e8f\u5165\u53e3",
    "\u2502   \u251c\u2500\u2500 clientwidget.h/cpp   \u5ba2\u6237\u7aef\u4e3b\u754c\u9762\u7c7b",
    "\u2502   \u251c\u2500\u2500 clientwidget.ui      \u754c\u9762\u5e03\u5c40\u6587\u4ef6",
    "\u2502   \u251c\u2500\u2500 mytcpclient.h/cpp    TCP\u5ba2\u6237\u7aef\u7c7b",
    "\u2502   \u251c\u2500\u2500 cartmanager.h/cpp     \u8d2d\u7269\u8f66\u7ba1\u7406\u7c7b",
    "\u2502   \u251c\u2500\u2500 dishitemwidget.h/cpp  \u83dc\u54c1\u6761\u76ee\u63a7\u4ef6",
    "\u2502   \u251c\u2500\u2500 cartitemwidget.h/cpp   \u8d2d\u7269\u8f66\u6761\u76ee\u63a7\u4ef6",
    "\u2502   \u2514\u2500\u2500 ...",
    "\u2514\u2500\u2500 protocol.md               \u901a\u4fe1\u534f\u8bae\u5b9a\u4e49\u6587\u6863",
  ]));

  // ===== 3. 数据库设计 =====
  children.push(heading1("3  \u6570\u636e\u5e93\u8bbe\u8ba1"));
  children.push(bodyPara("\u7cfb\u7edf\u4f7f\u7528 SQLite \u6570\u636e\u5e93\uff0c\u5171\u8bbe\u8ba1\u4e09\u5f20\u6570\u636e\u8868\uff1adish\uff08\u83dc\u5355\u8868\uff09\u3001orders\uff08\u8ba2\u5355\u4e3b\u8868\uff09\u3001order_detail\uff08\u8ba2\u5355\u660e\u7ec6\u8868\uff09\u3002\u83dc\u5355\u8868\u5b58\u50a8\u83dc\u54c1\u57fa\u672c\u4fe1\u606f\u548c\u5e93\u5b58\u72b6\u6001\uff0c\u8ba2\u5355\u4e3b\u8868\u8bb0\u5f55\u8ba2\u5355\u6982\u8981\u4fe1\u606f\uff0c\u8ba2\u5355\u660e\u7ec6\u8868\u901a\u8fc7\u5916\u952e\u5173\u8054\u8ba2\u5355\u548c\u83dc\u54c1\uff0c\u5b9e\u73b0\u4e00\u5bf9\u591a\u5173\u7cfb\u3002\u6570\u636e\u5e93\u5728\u670d\u52a1\u5668\u7aef\u542f\u52a8\u65f6\u81ea\u52a8\u521d\u59cb\u5316\uff0c\u82e5\u4e0d\u5b58\u5728\u5219\u81ea\u52a8\u521b\u5efa\u8868\u7ed3\u6784\u5e76\u63d2\u5165\u6d4b\u8bd5\u6570\u636e\u3002"));

  children.push(heading2("3.1  dish \u83dc\u5355\u8868"));
  children.push(makeTable(
    ["\u5b57\u6bb5\u540d", "\u7c7b\u578b", "\u7ea6\u675f", "\u8bf4\u660e"],
    [
      ["dish_id", "INTEGER", "PK, AUTO", "\u83dc\u54c1\u7f16\u53f7\uff0c\u4e3b\u952e\u81ea\u589e"],
      ["dish_name", "VARCHAR(50)", "NOT NULL", "\u83dc\u54c1\u540d\u79f0"],
      ["price", "DECIMAL(10,2)", "NOT NULL", "\u83dc\u54c1\u5355\u4ef7"],
      ["stock", "INTEGER", "NOT NULL", "\u83dc\u54c1\u5e93\u5b58\u6570\u91cf"],
      ["description", "VARCHAR(255)", "DEFAULT ''", "\u83dc\u54c1\u63cf\u8ff0\u4fe1\u606f"],
      ["status", "INTEGER", "DEFAULT 1", "\u83dc\u54c1\u72b6\u6001\uff1a1=\u4e0a\u67b6\uff0c0=\u4e0b\u67b6"],
    ],
    [20, 20, 20, 40]
  ));

  children.push(heading2("3.2  orders \u8ba2\u5355\u4e3b\u8868"));
  children.push(makeTable(
    ["\u5b57\u6bb5\u540d", "\u7c7b\u578b", "\u7ea6\u675f", "\u8bf4\u660e"],
    [
      ["order_id", "INTEGER", "PK, AUTO", "\u8ba2\u5355\u7f16\u53f7\uff0c\u4e3b\u952e\u81ea\u589e"],
      ["table_no", "VARCHAR(20)", "NOT NULL", "\u9910\u684c\u53f7"],
      ["people_count", "INTEGER", "DEFAULT 1", "\u5c31\u9910\u4eba\u6570"],
      ["total_price", "DECIMAL(10,2)", "NOT NULL", "\u8ba2\u5355\u603b\u4ef7"],
      ["create_time", "DATETIME", "NOT NULL", "\u4e0b\u5355\u65f6\u95f4"],
      ["status", "INTEGER", "DEFAULT 0", "\u8ba2\u5355\u72b6\u6001\uff1a0=\u5df2\u4e0b\u5355\uff0c1=\u5df2\u5b8c\u6210\uff0c2=\u5df2\u53d6\u6d88"],
    ],
    [20, 20, 20, 40]
  ));

  children.push(heading2("3.3  order_detail \u8ba2\u5355\u660e\u7ec6\u8868"));
  children.push(makeTable(
    ["\u5b57\u6bb5\u540d", "\u7c7b\u578b", "\u7ea6\u675f", "\u8bf4\u660e"],
    [
      ["detail_id", "INTEGER", "PK, AUTO", "\u660e\u7ec6\u7f16\u53f7\uff0c\u4e3b\u952e\u81ea\u589e"],
      ["order_id", "INTEGER", "FK->orders", "\u6240\u5c5e\u8ba2\u5355\u7f16\u53f7"],
      ["dish_id", "INTEGER", "FK->dish", "\u83dc\u54c1\u7f16\u53f7"],
      ["dish_name", "VARCHAR(50)", "NOT NULL", "\u83dc\u54c1\u540d\u79f0\uff08\u5197\u4f59\u4fdd\u5b58\uff09"],
      ["price", "DECIMAL(10,2)", "NOT NULL", "\u4e0b\u5355\u65f6\u83dc\u54c1\u5355\u4ef7"],
      ["count", "INTEGER", "DEFAULT 1", "\u8d2d\u4e70\u6570\u91cf"],
      ["subtotal", "DECIMAL(10,2)", "NOT NULL", "\u5c0f\u8ba1\u91d1\u989d = price * count"],
    ],
    [20, 20, 20, 40]
  ));

  children.push(heading2("3.4  \u8868\u5173\u7cfb\u8bf4\u660e"));
  children.push(bodyPara("orders \u8868\u4e0e order_detail \u8868\u4e3a\u4e00\u5bf9\u591a\u5173\u7cfb\uff0c\u4e00\u4e2a\u8ba2\u5355\u53ef\u5305\u542b\u591a\u4e2a\u83dc\u54c1\u660e\u7ec6\u3002order_detail \u901a\u8fc7 order_id \u5916\u952e\u5173\u8054 orders \u8868\uff0c\u901a\u8fc7 dish_id \u5916\u952e\u5173\u8054 dish \u8868\u3002dish_name \u548c price \u5728 order_detail \u4e2d\u5197\u4f59\u4fdd\u5b58\uff0c\u76ee\u7684\u662f\u5373\u4f7f\u83dc\u5355\u8868\u4e2d\u7684\u83dc\u54c1\u4fe1\u606f\u53d1\u751f\u53d8\u66f4\uff0c\u5386\u53f2\u8ba2\u5355\u4ecd\u80fd\u4fdd\u7559\u4e0b\u5355\u65f6\u7684\u51c6\u786e\u4ef7\u683c\u548c\u540d\u79f0\uff0c\u8fd9\u662f\u8ba2\u5355\u7cfb\u7edf\u4e2d\u5e38\u89c1\u7684\u53cd\u8303\u5f0f\u8bbe\u8ba1\u6a21\u5f0f\u3002"));

  // ===== 4. 通信协议设计 =====
  children.push(heading1("4  \u901a\u4fe1\u534f\u8bae\u8bbe\u8ba1"));
  children.push(bodyPara("\u5ba2\u6237\u7aef\u4e0e\u670d\u52a1\u5668\u7aef\u901a\u8fc7 TCP Socket \u8fdb\u884c\u901a\u4fe1\uff0c\u6240\u6709\u6570\u636e\u5747\u4f7f\u7528 JSON \u683c\u5f0f\u8fdb\u884c\u5e8f\u5217\u5316\u3002\u6bcf\u6761\u6d88\u606f\u4e3a\u4e00\u4e2a\u5b8c\u6574\u7684 JSON \u5bf9\u8c61\uff0c\u901a\u8fc7 type \u5b57\u6bb5\u533a\u5206\u6d88\u606f\u7c7b\u578b\u3002\u534f\u8bae\u8bbe\u8ba1\u9075\u5faa\u7b80\u6d01\u660e\u4e86\u7684\u539f\u5219\uff0c\u4ec5\u5b9a\u4e49\u4e86\u56db\u79cd\u6d88\u606f\u7c7b\u578b\uff1aget_menu\u3001menu_data\u3001submit_order\u3001order_result\uff0c\u8986\u76d6\u4e86\u7cfb\u7edf\u6240\u6709\u4e1a\u52a1\u573a\u666f\u3002"));

  children.push(heading2("4.1  \u8bf7\u6c42\u83dc\u5355\u534f\u8bae"));
  children.push(bodyPara("\u5ba2\u6237\u7aef\u53d1\u9001 get_menu \u8bf7\u6c42\uff0c\u670d\u52a1\u5668\u7aef\u54cd\u5e94 menu_data \u8fd4\u56de\u5168\u90e8\u4e0a\u67b6\u83dc\u54c1\u6570\u636e\u3002\u83dc\u5355\u6570\u636e\u5305\u542b\u83dc\u54c1\u7f16\u53f7\u3001\u540d\u79f0\u3001\u5355\u4ef7\u3001\u5e93\u5b58\u3001\u63cf\u8ff0\u548c\u72b6\u6001\u7b49\u5b57\u6bb5\uff0c\u5ba2\u6237\u7aef\u6536\u5230\u540e\u52a8\u6001\u6e32\u67d3\u83dc\u5355\u5217\u8868\u3002\u670d\u52a1\u5668\u7aef\u4f1a\u7f13\u5b58\u83dc\u5355\u6570\u636e\uff0c\u907f\u514d\u6bcf\u6b21\u8bf7\u6c42\u90fd\u67e5\u8be2\u6570\u636e\u5e93\uff0c\u63d0\u5347\u54cd\u5e94\u901f\u5ea6\u3002"));

  children.push(heading2("4.2  \u63d0\u4ea4\u8ba2\u5355\u534f\u8bae"));
  children.push(bodyPara("\u5ba2\u6237\u7aef\u53d1\u9001 submit_order \u8bf7\u6c42\uff0c\u643a\u5e26\u5b8c\u6574\u7684\u8ba2\u5355\u4fe1\u606f\uff0c\u5305\u62ec\u9910\u684c\u53f7\u3001\u5c31\u9910\u4eba\u6570\u3001\u603b\u4ef7\u3001\u4e0b\u5355\u65f6\u95f4\u548c\u83dc\u54c1\u660e\u7ec6\u5217\u8868\u3002\u670d\u52a1\u5668\u7aef\u6536\u5230\u540e\u4f7f\u7528\u4e8b\u52a1\u5904\u7406\u4fdd\u8bc1\u8ba2\u5355\u4e3b\u8868\u548c\u660e\u7ec6\u8868\u7684\u539f\u5b50\u6027\u5199\u5165\uff0c\u5e76\u81ea\u52a8\u6263\u51cf\u83dc\u54c1\u5e93\u5b58\u3002\u5904\u7406\u5b8c\u6210\u540e\u8fd4\u56de order_result \u54cd\u5e94\uff0c\u5305\u542b\u6210\u529f/\u5931\u8d25\u72b6\u6001\u3001\u8ba2\u5355\u53f7\u548c\u63d0\u793a\u4fe1\u606f\u3002"));

  children.push(heading2("4.3  \u6d88\u606f\u7c7b\u578b\u6c47\u603b"));
  children.push(makeTable(
    ["\u65b9\u5411", "\u6d88\u606f\u7c7b\u578b", "\u6838\u5fc3\u5b57\u6bb5", "\u8bf4\u660e"],
    [
      ["C->S", "get_menu", "type", "\u5ba2\u6237\u7aef\u8bf7\u6c42\u83dc\u5355\u6570\u636e"],
      ["S->C", "menu_data", "type, data", "\u670d\u52a1\u5668\u8fd4\u56de\u83dc\u5355\u6570\u636e\u6570\u7ec4"],
      ["C->S", "submit_order", "type, order", "\u5ba2\u6237\u7aef\u63d0\u4ea4\u8ba2\u5355"],
      ["S->C", "order_result", "type, success, order_id, msg", "\u670d\u52a1\u5668\u8fd4\u56de\u8ba2\u5355\u5904\u7406\u7ed3\u679c"],
    ],
    [10, 20, 35, 35]
  ));

  // ===== 5. 类设计 =====
  children.push(heading1("5  \u7c7b\u8bbe\u8ba1\u4e0e\u63a5\u53e3\u5b9a\u4e49"));
  children.push(bodyPara("\u7cfb\u7edf\u91c7\u7528\u6a21\u5757\u5316\u8bbe\u8ba1\uff0c\u5c06\u4e1a\u52a1\u903b\u8f91\u3001\u7f51\u7edc\u901a\u4fe1\u3001\u6570\u636e\u5e93\u64cd\u4f5c\u548c\u754c\u9762\u5c55\u793a\u5206\u79bb\u5230\u4e0d\u540c\u7684\u7c7b\u4e2d\u3002\u670d\u52a1\u5668\u7aef\u5305\u542b\u4e09\u4e2a\u6838\u5fc3\u7c7b\uff1aServerWidget\uff08\u754c\u9762\u63a7\u5236\uff09\u3001MyTcpServer\uff08\u7f51\u7edc\u901a\u4fe1\uff09\u3001DbManager\uff08\u6570\u636e\u5e93\u64cd\u4f5c\uff09\uff1b\u5ba2\u6237\u7aef\u5305\u542b\u4e94\u4e2a\u6838\u5fc3\u7c7b\uff1aClientWidget\uff08\u754c\u9762\u63a7\u5236\uff09\u3001MyTcpClient\uff08\u7f51\u7edc\u901a\u4fe1\uff09\u3001CartManager\uff08\u8d2d\u7269\u8f66\u903b\u8f91\uff09\u3001DishItemWidget\uff08\u83dc\u54c1\u6761\u76ee\u63a7\u4ef6\uff09\u3001CartItemWidget\uff08\u8d2d\u7269\u8f66\u6761\u76ee\u63a7\u4ef6\uff09\u3002\u5404\u7c7b\u4e4b\u95f4\u901a\u8fc7 Qt \u7684\u4fe1\u53f7\u69fd\u673a\u5236\u8fdb\u884c\u89e3\u8026\u901a\u4fe1\u3002"));

  children.push(heading2("5.1  \u670d\u52a1\u5668\u7aef\u7c7b\u8bbe\u8ba1"));

  children.push(heading3("5.1.1  DbManager \u6570\u636e\u5e93\u7ba1\u7406\u7c7b"));
  children.push(bodyPara("DbManager \u7c7b\u5c01\u88c5\u4e86\u6240\u6709\u6570\u636e\u5e93\u64cd\u4f5c\uff0c\u5305\u62ec\u6570\u636e\u5e93\u521d\u59cb\u5316\u3001\u83dc\u5355\u67e5\u8be2\u3001\u8ba2\u5355\u4fdd\u5b58\u548c\u5e93\u5b58\u66f4\u65b0\u3002\u8be5\u7c7b\u5728\u670d\u52a1\u5668\u542f\u52a8\u65f6\u81ea\u52a8\u521b\u5efa\u6570\u636e\u5e93\u8fde\u63a5\uff0c\u82e5\u6570\u636e\u5e93\u6587\u4ef6\u4e0d\u5b58\u5728\u5219\u81ea\u52a8\u521b\u5efa\u8868\u7ed3\u6784\u5e76\u63d2\u5165\u6d4b\u8bd5\u6570\u636e\u3002\u8ba2\u5355\u4fdd\u5b58\u64cd\u4f5c\u4f7f\u7528\u4e8b\u52a1\u5904\u7406\uff0c\u4fdd\u8bc1\u8ba2\u5355\u4e3b\u8868\u548c\u660e\u7ec6\u8868\u7684\u539f\u5b50\u6027\u5199\u5165\u3002"));
  children.push(makeTable(
    ["\u63a5\u53e3\u540d", "\u8fd4\u56de\u503c", "\u529f\u80fd\u8bf4\u660e"],
    [
      ["initDatabase()", "bool", "\u521d\u59cb\u5316\u6570\u636e\u5e93\uff0c\u521b\u5efa\u8868\u548c\u6d4b\u8bd5\u6570\u636e"],
      ["getMenuJson()", "QJsonArray", "\u83b7\u53d6\u6240\u6709\u4e0a\u67b6\u83dc\u54c1 JSON \u6570\u7ec4"],
      ["saveOrder(orderObj)", "int", "\u4fdd\u5b58\u8ba2\u5355\uff08\u4e8b\u52a1\u5904\u7406\uff09\uff0c\u8fd4\u56de\u8ba2\u5355ID"],
      ["getOrdersJson()", "QJsonArray", "\u83b7\u53d6\u6240\u6709\u8ba2\u5355\u5217\u8868 JSON \u6570\u7ec4"],
      ["updateDishStock(dishId, soldCount)", "bool", "\u66f4\u65b0\u83dc\u54c1\u5e93\u5b58\uff08\u4e0b\u5355\u540e\u6263\u51cf\uff09"],
    ],
    [35, 15, 50]
  ));

  children.push(heading3("5.1.2  MyTcpServer \u7f51\u7edc\u670d\u52a1\u7c7b"));
  children.push(bodyPara("MyTcpServer \u7c7b\u5c01\u88c5\u4e86 QTcpServer\uff0c\u8d1f\u8d23\u76d1\u542c\u5ba2\u6237\u7aef\u8fde\u63a5\u3001\u63a5\u6536\u548c\u89e3\u6790\u8bf7\u6c42\u3001\u53d1\u9001\u54cd\u5e94\u6570\u636e\u3002\u652f\u6301\u591a\u5ba2\u6237\u7aef\u540c\u65f6\u8fde\u63a5\uff0c\u7ef4\u62a4\u5ba2\u6237\u7aef\u5217\u8868\u3002\u6536\u5230\u8bf7\u6c42\u540e\u901a\u8fc7\u4fe1\u53f7\u901a\u77e5\u4e3b\u754c\u9762\u8fdb\u884c\u5904\u7406\uff0c\u5b9e\u73b0\u7f51\u7edc\u5c42\u4e0e\u4e1a\u52a1\u5c42\u7684\u89e3\u8026\u3002"));
  children.push(makeTable(
    ["\u63a5\u53e3/\u4fe1\u53f7", "\u7c7b\u578b", "\u529f\u80fd\u8bf4\u660e"],
    [
      ["start(port)", "\u65b9\u6cd5", "\u542f\u52a8\u670d\u52a1\u5668\u76d1\u542c"],
      ["stop()", "\u65b9\u6cd5", "\u505c\u6b62\u670d\u52a1\u5668"],
      ["setMenuData(data)", "\u65b9\u6cd5", "\u8bbe\u7f6e\u7f13\u5b58\u83dc\u5355\u6570\u636e"],
      ["sendOrderResult(socket, success, id, msg)", "\u65b9\u6cd5", "\u53d1\u9001\u8ba2\u5355\u5904\u7406\u7ed3\u679c"],
      ["menuRequested()", "\u4fe1\u53f7", "\u6536\u5230\u83dc\u5355\u8bf7\u6c42\u901a\u77e5"],
      ["orderReceived(orderObj)", "\u4fe1\u53f7", "\u6536\u5230\u8ba2\u5355\u63d0\u4ea4\u901a\u77e5"],
      ["clientConnected(info)", "\u4fe1\u53f7", "\u5ba2\u6237\u7aef\u8fde\u63a5\u901a\u77e5"],
    ],
    [40, 10, 50]
  ));

  children.push(heading3("5.1.3  ServerWidget \u670d\u52a1\u5668\u4e3b\u754c\u9762\u7c7b"));
  children.push(bodyPara("ServerWidget \u662f\u670d\u52a1\u5668\u7aef\u7684\u4e3b\u754c\u9762\u7c7b\uff0c\u8d1f\u8d23\u534f\u8c03 DbManager \u548c MyTcpServer \u7684\u5de5\u4f5c\u3002\u754c\u9762\u5305\u542b\u670d\u52a1\u5668\u542f\u505c\u63a7\u5236\u3001\u83dc\u5355\u5e93\u5b58\u663e\u793a\u3001\u8ba2\u5355\u5217\u8868\u663e\u793a\u3001\u5b9e\u65f6\u65f6\u949f\u548c\u901a\u4fe1\u65e5\u5fd7\u3002\u5f53\u6536\u5230\u83dc\u5355\u8bf7\u6c42\u65f6\uff0c\u4ece DbManager \u83b7\u53d6\u6570\u636e\u5e76\u901a\u8fc7 MyTcpServer \u53d1\u9001\u7ed9\u5ba2\u6237\u7aef\uff1b\u5f53\u6536\u5230\u8ba2\u5355\u65f6\uff0c\u8c03\u7528 DbManager \u4fdd\u5b58\u8ba2\u5355\u5e76\u66f4\u65b0\u754c\u9762\u663e\u793a\u3002"));

  children.push(heading2("5.2  \u5ba2\u6237\u7aef\u7c7b\u8bbe\u8ba1"));

  children.push(heading3("5.2.1  MyTcpClient \u7f51\u7edc\u5ba2\u6237\u7aef\u7c7b"));
  children.push(bodyPara("MyTcpClient \u7c7b\u5c01\u88c5\u4e86 QTcpSocket\uff0c\u63d0\u4f9b\u8fde\u63a5\u670d\u52a1\u5668\u3001\u53d1\u9001\u8bf7\u6c42\u3001\u63a5\u6536\u54cd\u5e94\u7684\u529f\u80fd\u3002\u5185\u90e8\u7ef4\u62a4\u6570\u636e\u7f13\u51b2\u533a\uff0c\u5904\u7406\u7c98\u5305\u95ee\u9898\uff0c\u786e\u4fdd\u5b8c\u6574 JSON \u6d88\u606f\u7684\u6b63\u786e\u89e3\u6790\u3002\u8fde\u63a5\u5931\u8d25\u65f6\u81ea\u52a8\u53d1\u51fa\u9519\u8bef\u4fe1\u53f7\uff0c\u652f\u6301\u8d85\u65f6\u7b49\u5f85\u3002"));
  children.push(makeTable(
    ["\u63a5\u53e3/\u4fe1\u53f7", "\u7c7b\u578b", "\u529f\u80fd\u8bf4\u660e"],
    [
      ["connectToServer(host, port)", "\u65b9\u6cd5", "\u8fde\u63a5\u670d\u52a1\u5668\uff0c3\u79d2\u8d85\u65f6"],
      ["disconnectFromServer()", "\u65b9\u6cd5", "\u65ad\u5f00\u8fde\u63a5"],
      ["requestMenu()", "\u65b9\u6cd5", "\u53d1\u9001\u83dc\u5355\u8bf7\u6c42"],
      ["submitOrder(orderObj)", "\u65b9\u6cd5", "\u63d0\u4ea4\u8ba2\u5355"],
      ["menuReceived(data)", "\u4fe1\u53f7", "\u6536\u5230\u83dc\u5355\u6570\u636e"],
      ["orderResult(success, id, msg)", "\u4fe1\u53f7", "\u6536\u5230\u8ba2\u5355\u7ed3\u679c"],
    ],
    [40, 10, 50]
  ));

  children.push(heading3("5.2.2  CartManager \u8d2d\u7269\u8f66\u7ba1\u7406\u7c7b"));
  children.push(bodyPara("CartManager \u662f\u5ba2\u6237\u7aef\u7684\u6838\u5fc3\u4e1a\u52a1\u7c7b\uff0c\u7ba1\u7406\u8d2d\u7269\u8f66\u4e2d\u6240\u6709\u83dc\u54c1\u7684\u589e\u5220\u6539\u67e5\u3002\u652f\u6301\u6dfb\u52a0\u83dc\u54c1\uff08\u91cd\u590d\u5219\u7d2f\u52a0\u6570\u91cf\uff09\u3001\u4fee\u6539\u6570\u91cf\u3001\u5220\u9664\u83dc\u54c1\u3001\u6e05\u7a7a\u8d2d\u7269\u8f66\u3001\u81ea\u52a8\u8ba1\u7b97\u603b\u4ef7\u3002\u5f53\u8d2d\u7269\u8f66\u5185\u5bb9\u53d8\u5316\u65f6\u81ea\u52a8\u53d1\u51fa cartChanged \u548c totalPriceChanged \u4fe1\u53f7\uff0c\u901a\u77e5\u754c\u9762\u5237\u65b0\u3002\u8be5\u7c7b\u8fd8\u63d0\u4f9b toJsonArray() \u65b9\u6cd5\uff0c\u5c06\u8d2d\u7269\u8f66\u5185\u5bb9\u8f6c\u4e3a JSON \u6570\u7ec4\u7528\u4e8e\u8ba2\u5355\u63d0\u4ea4\u3002"));
  children.push(makeTable(
    ["\u63a5\u53e3/\u4fe1\u53f7", "\u7c7b\u578b", "\u529f\u80fd\u8bf4\u660e"],
    [
      ["addItem(dishId, name, price, count)", "\u65b9\u6cd5", "\u6dfb\u52a0\u83dc\u54c1\uff0c\u5df2\u5b58\u5728\u5219\u7d2f\u52a0\u6570\u91cf"],
      ["updateItem(dishId, newCount)", "\u65b9\u6cd5", "\u4fee\u6539\u6570\u91cf\uff0c\u6570\u91cf\u22640\u5219\u5220\u9664"],
      ["removeItem(dishId)", "\u65b9\u6cd5", "\u5220\u9664\u6307\u5b9a\u83dc\u54c1"],
      ["clearCart()", "\u65b9\u6cd5", "\u6e05\u7a7a\u8d2d\u7269\u8f66"],
      ["getTotalPrice()", "\u65b9\u6cd5", "\u83b7\u53d6\u603b\u4ef7"],
      ["toJsonArray()", "\u65b9\u6cd5", "\u8f6c\u4e3a JSON \u6570\u7ec4"],
      ["cartChanged()", "\u4fe1\u53f7", "\u8d2d\u7269\u8f66\u5185\u5bb9\u53d8\u5316"],
      ["totalPriceChanged(total)", "\u4fe1\u53f7", "\u603b\u4ef7\u53d8\u5316"],
    ],
    [40, 10, 50]
  ));

  children.push(heading3("5.2.3  DishItemWidget / CartItemWidget \u81ea\u5b9a\u4e49\u63a7\u4ef6"));
  children.push(bodyPara("DishItemWidget \u662f\u83dc\u5355\u5217\u8868\u4e2d\u7684\u5355\u4e2a\u83dc\u54c1\u5c55\u793a\u63a7\u4ef6\uff0c\u5305\u542b\u83dc\u540d\u3001\u4ef7\u683c\u3001\u5e93\u5b58\u3001\u63cf\u8ff0\u3001\u6570\u91cf\u9009\u62e9\u548c\u201c\u52a0\u5165\u8d2d\u7269\u8f66\u201d\u6309\u94ae\u3002\u70b9\u51fb\u6309\u94ae\u540e\u53d1\u51fa addToCart \u4fe1\u53f7\uff0c\u643a\u5e26\u83dc\u54c1\u4fe1\u606f\u3002CartItemWidget \u662f\u8d2d\u7269\u8f66\u5217\u8868\u4e2d\u7684\u5355\u4e2a\u6761\u76ee\u63a7\u4ef6\uff0c\u5305\u542b\u83dc\u540d\u3001\u5355\u4ef7\u3001\u53ef\u4fee\u6539\u7684\u6570\u91cf\u3001\u5c0f\u8ba1\u548c\u5220\u9664\u6309\u94ae\u3002\u4fee\u6539\u6570\u91cf\u65f6\u81ea\u52a8\u66f4\u65b0\u5c0f\u8ba1\u5e76\u53d1\u51fa countChanged \u4fe1\u53f7\uff0c\u70b9\u51fb\u5220\u9664\u53d1\u51fa removeRequested \u4fe1\u53f7\u3002\u8fd9\u4e24\u4e2a\u63a7\u4ef6\u5747\u7ee7\u627f\u81ea QWidget\uff0c\u901a\u8fc7\u81ea\u5b9a\u4e49\u5e03\u5c40\u548c\u6837\u5f0f\u8868\u5b9e\u73b0\u7f8e\u89c2\u7684\u754c\u9762\u6548\u679c\u3002"));

  // ===== 6. 界面设计 =====
  children.push(heading1("6  \u754c\u9762\u5e03\u5c40\u8bbe\u8ba1"));
  children.push(bodyPara("\u7cfb\u7edf\u754c\u9762\u91c7\u7528 Qt Designer \u8bbe\u8ba1\uff0c\u901a\u8fc7 .ui \u6587\u4ef6\u5b9e\u73b0\u53ef\u89c6\u5316\u5e03\u5c40\u3002\u670d\u52a1\u5668\u7aef\u548c\u5ba2\u6237\u7aef\u5747\u91c7\u7528\u4e3b\u7a97\u53e3\u5e03\u5c40\uff0c\u4e0d\u4f7f\u7528\u591a\u7a97\u53e3\u3002\u754c\u9762\u8bbe\u8ba1\u9075\u5faa\u7b80\u6d01\u5b9e\u7528\u7684\u539f\u5219\uff0c\u91cd\u70b9\u7a81\u51fa\u6838\u5fc3\u64cd\u4f5c\u6d41\u7a0b\u3002"));

  children.push(heading2("6.1  \u670d\u52a1\u5668\u7aef\u754c\u9762"));
  children.push(bodyPara("\u670d\u52a1\u5668\u7aef\u754c\u9762\u91c7\u7528\u4e09\u5c42\u5e03\u5c40\uff1a\u9876\u90e8\u4e3a\u63a7\u5236\u680f\uff08\u5b9e\u65f6\u65f6\u949f\u3001\u670d\u52a1\u5668\u72b6\u6001\u3001\u7aef\u53e3\u914d\u7f6e\u3001\u542f\u505c\u6309\u94ae\uff09\uff0c\u4e2d\u90e8\u4e3a Tab \u9009\u9879\u5361\uff08\u83dc\u5355\u7ba1\u7406\u548c\u8ba2\u5355\u5217\u8868\u4e24\u4e2a\u9875\u7b7e\uff09\uff0c\u5e95\u90e8\u4e3a\u901a\u4fe1\u65e5\u5fd7\u533a\u57df\u3002\u83dc\u5355\u7ba1\u7406\u9875\u7b7e\u4f7f\u7528 QTableWidget \u5c55\u793a\u83dc\u54c1\u7f16\u53f7\u3001\u540d\u79f0\u3001\u4ef7\u683c\u3001\u5e93\u5b58\u3001\u63cf\u8ff0\u548c\u72b6\u6001\uff0c\u652f\u6301\u5237\u65b0\u64cd\u4f5c\u3002\u8ba2\u5355\u5217\u8868\u9875\u7b7e\u5c55\u793a\u8ba2\u5355\u53f7\u3001\u9910\u684c\u53f7\u3001\u4eba\u6570\u3001\u603b\u4ef7\u3001\u65f6\u95f4\u548c\u72b6\u6001\uff0c\u540c\u6837\u652f\u6301\u5237\u65b0\u3002\u65e5\u5fd7\u533a\u57df\u4f7f\u7528 QTextEdit \u53ea\u8bfb\u663e\u793a\uff0c\u8bb0\u5f55\u5ba2\u6237\u7aef\u8fde\u63a5\u3001\u8bf7\u6c42\u548c\u8ba2\u5355\u4e8b\u4ef6\u3002"));

  children.push(heading2("6.2  \u5ba2\u6237\u7aef\u754c\u9762"));
  children.push(bodyPara("\u5ba2\u6237\u7aef\u754c\u9762\u91c7\u7528\u5de6\u53f3\u5206\u680f\u5e03\u5c40\uff1a\u5de6\u4fa7\u4e3a\u83dc\u5355\u5217\u8868\u533a\uff08\u4f7f\u7528 QListWidget \u5d4c\u5165 DishItemWidget \u81ea\u5b9a\u4e49\u63a7\u4ef6\uff09\uff0c\u53f3\u4fa7\u4e3a\u8d2d\u7269\u8f66\u533a\uff08\u4f7f\u7528 QListWidget \u5d4c\u5165 CartItemWidget \u81ea\u5b9a\u4e49\u63a7\u4ef6\uff09\u3002\u9876\u90e8\u4e3a\u63a7\u5236\u680f\uff08\u65f6\u949f\u3001\u8fde\u63a5\u72b6\u6001\u3001\u670d\u52a1\u5668\u914d\u7f6e\u3001\u83b7\u53d6\u83dc\u5355\u6309\u94ae\uff09\uff0c\u5e95\u90e8\u4e3a\u8ba2\u5355\u4fe1\u606f\u680f\uff08\u9910\u684c\u53f7\u3001\u5c31\u9910\u4eba\u6570\u3001\u603b\u4ef7\u663e\u793a\u3001\u63d0\u4ea4\u8ba2\u5355\u6309\u94ae\u3001\u6e05\u7a7a\u8d2d\u7269\u8f66\u6309\u94ae\uff09\u3002\u83dc\u5355\u5217\u8868\u548c\u8d2d\u7269\u8f66\u5217\u8868\u5747\u652f\u6301\u6eda\u52a8\u6d4f\u89c8\uff0c\u603b\u4ef7\u5b9e\u65f6\u66f4\u65b0\u3002"));

  // ===== 7. 关键实现细节 =====
  children.push(heading1("7  \u5173\u952e\u5b9e\u73b0\u7ec6\u8282"));

  children.push(heading2("7.1  \u8ba2\u5355\u4e8b\u52a1\u5904\u7406"));
  children.push(bodyPara("\u8ba2\u5355\u4fdd\u5b58\u662f\u7cfb\u7edf\u4e2d\u6700\u5173\u952e\u7684\u64cd\u4f5c\uff0c\u5fc5\u987b\u4fdd\u8bc1\u6570\u636e\u4e00\u81f4\u6027\u3002DbManager::saveOrder() \u65b9\u6cd5\u4f7f\u7528\u6570\u636e\u5e93\u4e8b\u52a1\u5904\u7406\uff0c\u5c06\u8ba2\u5355\u4e3b\u8868\u63d2\u5165\u548c\u660e\u7ec6\u8868\u6279\u91cf\u63d2\u5165\u5305\u88f9\u5728\u540c\u4e00\u4e2a\u4e8b\u52a1\u4e2d\u3002\u5982\u679c\u4efb\u4f55\u4e00\u6b65\u5931\u8d25\uff0c\u6574\u4e2a\u4e8b\u52a1\u56de\u6eda\uff0c\u907f\u514d\u51fa\u73b0\u6709\u8ba2\u5355\u4e3b\u8bb0\u5f55\u4f46\u65e0\u660e\u7ec6\u7684\u60c5\u51b5\u3002\u540c\u65f6\uff0c\u4e0b\u5355\u6210\u529f\u540e\u81ea\u52a8\u6263\u51cf\u5bf9\u5e94\u83dc\u54c1\u7684\u5e93\u5b58\u6570\u91cf\uff0c\u5e93\u5b58\u66f4\u65b0\u4e5f\u7eb3\u5165\u4e8b\u52a1\u8303\u56f4\u3002\u4e8b\u52a1\u5904\u7406\u7684\u6838\u5fc3\u6d41\u7a0b\u4e3a\uff1a\u5f00\u542f\u4e8b\u52a1 \u2192 \u63d2\u5165\u8ba2\u5355\u4e3b\u8868 \u2192 \u83b7\u53d6\u81ea\u589eID \u2192 \u6279\u91cf\u63d2\u5165\u660e\u7ec6\u8868 \u2192 \u6263\u51cf\u5e93\u5b58 \u2192 \u63d0\u4ea4\u4e8b\u52a1\uff08\u5931\u8d25\u5219\u56de\u6eda\uff09\u3002"));

  children.push(heading2("7.2  \u5b9e\u65f6\u65f6\u949f\u663e\u793a"));
  children.push(bodyPara("\u670d\u52a1\u5668\u7aef\u548c\u5ba2\u6237\u7aef\u5747\u4f7f\u7528 QTimer \u5b9e\u73b0\u5b9e\u65f6\u65f6\u949f\u663e\u793a\u3002\u5b9a\u65f6\u5668\u6bcf\u79d2\u89e6\u53d1\u4e00\u6b21 timeout \u4fe1\u53f7\uff0c\u5728\u69fd\u51fd\u6570\u4e2d\u8c03\u7528 QDateTime::currentDateTime() \u83b7\u53d6\u5f53\u524d\u65f6\u95f4\u5e76\u66f4\u65b0 QLabel \u663e\u793a\u3002\u65f6\u95f4\u683c\u5f0f\u4e3a\u201c\u5f53\u524d\u65f6\u95f4\uff1ayyyy-MM-dd hh:mm:ss\u201d\uff0c\u542f\u52a8\u65f6\u7acb\u5373\u663e\u793a\u4e00\u6b21\uff0c\u4e4b\u540e\u6bcf\u79d2\u81ea\u52a8\u5237\u65b0\u3002\u8fd9\u79cd\u5b9e\u73b0\u65b9\u5f0f\u7b80\u5355\u9ad8\u6548\uff0c\u4e0d\u4f1a\u5bf9\u7cfb\u7edf\u6027\u80fd\u4ea7\u751f\u660e\u663e\u5f71\u54cd\u3002"));

  children.push(heading2("7.3  \u7c98\u5305\u5904\u7406\u4e0e JSON \u89e3\u6790"));
  children.push(bodyPara("TCP \u901a\u4fe1\u5b58\u5728\u7c98\u5305\u95ee\u9898\uff0c\u5373\u4e00\u6b21\u63a5\u6536\u7684\u6570\u636e\u53ef\u80fd\u5305\u542b\u591a\u6761\u6d88\u606f\uff0c\u6216\u4e00\u6761\u6d88\u606f\u88ab\u5206\u6210\u591a\u6b21\u63a5\u6536\u3002MyTcpClient \u4e2d\u7ef4\u62a4\u4e86\u4e00\u4e2a\u6570\u636e\u7f13\u51b2\u533a m_buffer\uff0c\u6bcf\u6b21\u6536\u5230\u6570\u636e\u65f6\u8ffd\u52a0\u5230\u7f13\u51b2\u533a\uff0c\u7136\u540e\u5c1d\u8bd5\u89e3\u6790\u5b8c\u6574\u7684 JSON\u3002\u5982\u679c\u89e3\u6790\u6210\u529f\u5219\u6e05\u7a7a\u7f13\u51b2\u533a\u5e76\u5904\u7406\u6d88\u606f\uff0c\u5982\u679c\u89e3\u6790\u5931\u8d25\u5219\u4fdd\u7559\u7f13\u51b2\u533a\u7b49\u5f85\u66f4\u591a\u6570\u636e\u5230\u8fbe\u3002\u8fd9\u79cd\u65b9\u5f0f\u80fd\u6709\u6548\u5904\u7406\u7c98\u5305\u548c\u534a\u5305\u95ee\u9898\uff0c\u4fdd\u8bc1\u901a\u4fe1\u7684\u53ef\u9760\u6027\u3002"));

  children.push(heading2("7.4  \u81ea\u5b9a\u4e49\u63a7\u4ef6\u5d4c\u5165 QListWidget"));
  children.push(bodyPara("\u83dc\u5355\u5217\u8868\u548c\u8d2d\u7269\u8f66\u5217\u8868\u5747\u4f7f\u7528 QListWidget \u642d\u914d\u81ea\u5b9a\u4e49 Widget \u7684\u65b9\u5f0f\u5b9e\u73b0\u3002\u5177\u4f53\u505a\u6cd5\u662f\uff1a\u521b\u5efa QListWidgetItem \u5e76\u8bbe\u7f6e\u5176\u5927\u5c0f\uff0c\u7136\u540e\u5c06\u81ea\u5b9a\u4e49 Widget\uff08DishItemWidget \u6216 CartItemWidget\uff09\u8bbe\u7f6e\u4e3a\u8be5 Item \u7684\u5173\u8054\u63a7\u4ef6\u3002\u81ea\u5b9a\u4e49\u63a7\u4ef6\u7684\u4fe1\u53f7\u901a\u8fc7 lambda \u6216 connect \u8fde\u63a5\u5230\u4e3b\u754c\u9762\u7684\u69fd\u51fd\u6570\uff0c\u5b9e\u73b0\u4e8b\u4ef6\u7684\u5c42\u5c42\u4f20\u9012\u3002\u8fd9\u79cd\u65b9\u5f0f\u65e2\u4fdd\u8bc1\u4e86\u754c\u9762\u7684\u7f8e\u89c2\u6027\uff0c\u53c8\u4fdd\u6301\u4e86\u4ee3\u7801\u7684\u6e05\u6670\u6027\u3002"));

  // ===== 8. 编译与运行 =====
  children.push(heading1("8  \u7f16\u8bd1\u4e0e\u8fd0\u884c\u6307\u5357"));
  children.push(heading2("8.1  \u73af\u5883\u8981\u6c42"));
  children.push(makeTable(
    ["\u73af\u5883\u9879", "\u8981\u6c42"],
    [
      ["\u64cd\u4f5c\u7cfb\u7edf", "Windows 10+ / Ubuntu 18.04+ / macOS 10.14+"],
      ["Qt \u7248\u672c", "Qt 5.12 \u53ca\u4ee5\u4e0a\uff08\u9700\u5305\u542b Qt Network \u548c Qt SQL \u6a21\u5757\uff09"],
      ["\u7f16\u8bd1\u5668", "GCC 7+ / MSVC 2017+ / Clang 6+ \uff08\u652f\u6301 C++17\uff09"],
      ["\u6784\u5efa\u5de5\u5177", "qmake\uff08\u968f Qt \u81ea\u5e26\uff09\u6216 CMake 3.16+"],
    ],
    [30, 70]
  ));

  children.push(heading2("8.2  \u7f16\u8bd1\u6b65\u9aa4"));
  children.push(bodyPara("\u670d\u52a1\u5668\u7aef\u7f16\u8bd1\uff1a\u8fdb\u5165 Server \u76ee\u5f55\uff0c\u6267\u884c qmake Server.pro \u751f\u6210 Makefile\uff0c\u7136\u540e\u6267\u884c make \u8fdb\u884c\u7f16\u8bd1\u3002\u5ba2\u6237\u7aef\u7f16\u8bd1\uff1a\u8fdb\u5165 Client \u76ee\u5f55\uff0c\u6267\u884c qmake Client.pro \u751f\u6210 Makefile\uff0c\u7136\u540e\u6267\u884c make \u8fdb\u884c\u7f16\u8bd1\u3002\u5728 Windows \u5e73\u53f0\u4e0a\u4e5f\u53ef\u4ee5\u4f7f\u7528 Qt Creator \u76f4\u63a5\u6253\u5f00 .pro \u6587\u4ef6\u8fdb\u884c\u7f16\u8bd1\u8fd0\u884c\u3002\u7f16\u8bd1\u5b8c\u6210\u540e\uff0c\u5148\u542f\u52a8\u670d\u52a1\u5668\u7aef\u7a0b\u5e8f\uff0c\u518d\u542f\u52a8\u5ba2\u6237\u7aef\u7a0b\u5e8f\u3002"));

  children.push(heading2("8.3  \u8fd0\u884c\u6d41\u7a0b"));
  children.push(bodyPara("\u7cfb\u7edf\u8fd0\u884c\u5206\u4e3a\u4ee5\u4e0b\u6b65\u9aa4\uff1a\u7b2c\u4e00\u6b65\uff0c\u542f\u52a8\u670d\u52a1\u5668\u7aef\u7a0b\u5e8f\uff0c\u70b9\u51fb\u201c\u542f\u52a8\u670d\u52a1\u5668\u201d\u6309\u94ae\uff0c\u670d\u52a1\u5668\u5f00\u59cb\u76d1\u542c\u6307\u5b9a\u7aef\u53e3\uff1b\u7b2c\u4e8c\u6b65\uff0c\u542f\u52a8\u5ba2\u6237\u7aef\u7a0b\u5e8f\uff0c\u8f93\u5165\u670d\u52a1\u5668\u5730\u5740\u548c\u7aef\u53e3\uff0c\u70b9\u51fb\u201c\u8fde\u63a5\u670d\u52a1\u5668\u201d\uff1b\u7b2c\u4e09\u6b65\uff0c\u70b9\u51fb\u201c\u83b7\u53d6\u83dc\u5355\u201d\u52a0\u8f7d\u83dc\u54c1\u5217\u8868\uff1b\u7b2c\u56db\u6b65\uff0c\u9009\u62e9\u83dc\u54c1\u5e76\u70b9\u51fb\u201c\u52a0\u5165\u8d2d\u7269\u8f66\u201d\uff1b\u7b2c\u4e94\u6b65\uff0c\u586b\u5199\u9910\u684c\u53f7\u548c\u5c31\u9910\u4eba\u6570\uff0c\u70b9\u51fb\u201c\u63d0\u4ea4\u8ba2\u5355\u201d\u5b8c\u6210\u4e0b\u5355\u3002\u670d\u52a1\u5668\u7aef\u4f1a\u81ea\u52a8\u66f4\u65b0\u8ba2\u5355\u5217\u8868\u548c\u83dc\u5355\u5e93\u5b58\u663e\u793a\u3002"));

  return {
    properties: {
      page: {
        size: { width: 11906, height: 16838 },
        margin: { top: 1440, bottom: 1440, left: 1701, right: 1417 },
      },
    },
    headers: {
      default: new Header({
        children: [new Paragraph({
          alignment: AlignmentType.RIGHT,
          children: [new TextRun({ text: "Qt\u70b9\u9910\u7ec8\u7aef\u7cfb\u7edf \u2014 \u9879\u76ee\u8bbe\u8ba1\u6587\u6863", size: 18, color: P.secondary, font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" } })]
        })]
      })
    },
    footers: {
      default: new Footer({
        children: [new Paragraph({
          alignment: AlignmentType.CENTER,
          children: [new TextRun({ children: [PageNumber.CURRENT], size: 18, color: P.secondary })]
        })]
      })
    },
    children,
  };
}

// ====== Main ======
async function main() {
  const doc = new Document({
    styles: {
      default: {
        document: {
          run: {
            font: { ascii: "Calibri", eastAsia: "Microsoft YaHei" },
            size: 24,
            color: P.body,
          },
          paragraph: {
            spacing: { line: 312 },
          },
        },
        heading1: {
          run: { font: { ascii: "Calibri", eastAsia: "SimHei" }, size: 32, bold: true, color: P.primary },
          paragraph: { spacing: { before: 360, after: 160, line: 312 } },
        },
        heading2: {
          run: { font: { ascii: "Calibri", eastAsia: "SimHei" }, size: 28, bold: true, color: P.primary },
          paragraph: { spacing: { before: 280, after: 120, line: 312 } },
        },
        heading3: {
          run: { font: { ascii: "Calibri", eastAsia: "SimHei" }, size: 24, bold: true, color: P.primary },
          paragraph: { spacing: { before: 200, after: 100, line: 312 } },
        },
      },
    },
    sections: [buildCover(), buildBody()],
  });

  const buffer = await Packer.toBuffer(doc);
  fs.writeFileSync("/home/z/my-project/download/OrderSystem/Qt\u70b9\u9910\u7ec8\u7aef\u7cfb\u7edf_\u9879\u76ee\u8bbe\u8ba1\u6587\u6863.docx", buffer);
  console.log("Document generated successfully!");
}

main().catch(console.error);
