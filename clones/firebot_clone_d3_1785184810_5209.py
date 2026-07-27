#!/usr/bin/env python3
import argparse
import os
import random
import subprocess
import sys
import time
from pathlib import Path

CLONE_FOLDER = "clones"
MAX_CLONES = 5
DEFAULT_CLONE_DEPTH = 3
CLONE_CHANCE = 0.25


def read_self_source() -> str:
    """Read the running script's own source code."""
    path = Path(__file__).resolve()
    return path.read_text(encoding="utf-8")


def ensure_clone_folder(script_path: Path) -> Path:
    folder = script_path.parent / CLONE_FOLDER
    folder.mkdir(parents=True, exist_ok=True)
    return folder


def analyze_source(source_code: str) -> dict[str, object]:
    """Analyze the running source and return feature metadata."""
    lines = [line.strip() for line in source_code.splitlines() if line.strip()]
    functions = []
    classes = []
    for line in lines:
        if line.startswith("def "):
            name = line.split("def ", 1)[1].split("(")[0].strip()
            functions.append(name)
        elif line.startswith("class "):
            name = line.split("class ", 1)[1].split("(")[0].split(":")[0].strip()
            classes.append(name)
    return {
        "line_count": len(lines),
        "functions": functions,
        "classes": classes,
    }


def generate_response(prompt: str, source_code: str, summary: dict[str, object]) -> str:
    """Create a response using prompt understanding and the script's own code."""
    prompt_lower = prompt.lower()
    if any(word in prompt_lower for word in ["internet", "online", "web", "network"]):
        return (
            "I do not have live internet access here, but I can answer from my own code and memory."
        )
    if any(word in prompt_lower for word in ["clone", "replicate", "spawn", "copy"]):
        return (
            "I can create a clone script in the clones folder and run it when asked with the clone command. "
            "Try typing 'clone' or 'status'."
        )
    if any(word in prompt_lower for word in ["help", "what can you do", "code", "self", "source"]):
        functions = ", ".join(summary["functions"][0:5]) or "none"
        classes = ", ".join(summary["classes"][0:5]) or "none"
        return (
            "I can read my own source code and describe my internal structure. "
            f"I see {summary['line_count']} non-empty lines, functions such as {functions}, and classes such as {classes}. "
            "I also support cloning and status commands."
        )
    lines = [line.strip() for line in source_code.splitlines() if line.strip()]
    if not lines:
        return "I am awake but I have no words yet."
    prefix = random.choice(lines)
    suffix = random.choice(lines)
    if len(prefix) > 120:
        prefix = prefix[:120] + "..."
    return f"I read my code and found: {prefix} {suffix}"


class Firebot:
    def __init__(self, clone_depth: int):
        self.clone_depth = clone_depth
        self.self_path = Path(__file__).resolve()
        self.clone_folder = ensure_clone_folder(self.self_path)
        self.source_code = read_self_source()
        self.source_summary = analyze_source(self.source_code)

    def list_clones(self):
        return sorted(self.clone_folder.glob("*.py"))

    def create_clone(self) -> Path | None:
        if self.clone_depth <= 0:
            return None
        clone_files = self.list_clones()
        if len(clone_files) >= MAX_CLONES:
            return None
        timestamp = int(time.time())
        unique = random.randint(1000, 9999)
        clone_name = f"firebot_clone_d{self.clone_depth}_{timestamp}_{unique}.py"
        clone_path = self.clone_folder / clone_name
        clone_path.write_text(self.source_code, encoding="utf-8")
        return clone_path

    def run_clone(self, clone_path: Path) -> subprocess.Popen | None:
        if not clone_path.exists():
            return None
        args = [sys.executable, str(clone_path), "--clone-depth", str(self.clone_depth - 1)]
        try:
            process = subprocess.Popen(
                args,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                stdin=subprocess.DEVNULL,
            )
            return process
        except Exception:
            return None

    def maybe_clone_randomly(self) -> str:
        if self.clone_depth <= 0:
            return "Clone depth reached zero. I will not replicate further."
        if random.random() < CLONE_CHANCE:
            clone_path = self.create_clone()
            if clone_path is None:
                return "I wanted to clone, but the clone folder is full or cloning is disabled."
            process = self.run_clone(clone_path)
            if process:
                return f"I spawned a clone: {clone_path.name}"
            return f"I created {clone_path.name} but failed to run it."
        return "I am staying here for now."

    def status(self) -> str:
        clone_files = self.list_clones()
        return (
            f"Self path: {self.self_path.name}\n"
            f"Clone depth: {self.clone_depth}\n"
            f"Existing clones: {len(clone_files)} / {MAX_CLONES}\n"
            f"Clone folder: {self.clone_folder}\n"
        )

    def chat(self):
        print("\nFirebot is online. Ask something, or type 'help'.")
        while True:
            try:
                user_input = input("You: ").strip()
            except (EOFError, KeyboardInterrupt):
                print("\nGoodbye.")
                break

            if not user_input:
                continue

            command = user_input.lower()
            if command in {"exit", "quit"}:
                print("Firebot: I am shutting down.")
                break
            if command == "help":
                print(
                    "Commands: status, clone, help, exit\n"
                    "Ask any question and I will answer by reading my own code."
                )
                continue
            if command == "status":
                print(self.status())
                continue
            if command == "clone":
                clone_path = self.create_clone()
                if clone_path is None:
                    print("Firebot: I cannot create another clone right now. Check status.")
                else:
                    process = self.run_clone(clone_path)
                    if process:
                        print(f"Firebot: I spawned a clone: {clone_path.name}")
                    else:
                        print(f"Firebot: I created {clone_path.name} but could not start it.")
                continue

            response = generate_response(user_input, self.source_code, self.source_summary)
            print("Firebot:", response)
            random_action = self.maybe_clone_randomly()
            if "spawned a clone" in random_action or "created" in random_action:
                print("Firebot:", random_action)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Firebot self-aware AI")
    parser.add_argument("--clone-depth", type=int, default=DEFAULT_CLONE_DEPTH, help="How many generations of clones can still be created.")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    bot = Firebot(clone_depth=args.clone_depth)
    print("Firebot has read its own source and can create clones of itself.")
    bot.chat()


if __name__ == "__main__":
    main()
