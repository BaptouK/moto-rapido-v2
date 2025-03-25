"use client";

import {InputOTP, InputOTPGroup, InputOTPSeparator, InputOTPSlot} from "@/components/ui/input-otp";
import {Button} from "@/components/ui/button";

import {
    Table,
    TableBody, TableCaption,
    TableCell,
    TableHead,
    TableHeader,
    TableRow,
} from "@/components/ui/table"
import Image from "next/image";
import {ScrollArea} from "@/components/ui/scroll-area";
import {Check, ChevronsUpDown, Copy, Crown, User} from "lucide-react";
import {Dispatch, SetStateAction, useState} from "react";

import {
    Command,
    CommandEmpty,
    CommandGroup,
    CommandInput,
    CommandItem,
    CommandList,
} from "@/components/ui/command"
import {
    Popover,
    PopoverContent,
    PopoverTrigger,
} from "@/components/ui/popover"
import {cn} from "@/lib/utils";

export type LobbyProps = {
    code: string;
    owner: string;
    players: string[];
}

type Game = {
    label: string;
    value: string;
}

const allGames:Game[] = [
    {label: "Calcul", value: "calcul"},
    {label: "Typing test", value: "typingtest"},
    {label: "AimLab", value: "aimlab"},
    {label: "PianoTiles", value: "pianotiles"},
    {label: "Crier sur le poste", value: "crier"},
    {label: "Taper l'alphabet à l'envers", value: "alphabet"},
    {label: "Test Références", value: "testref"},
    {label: "Japochi", value: "japochi"},
    {label: "Petit bac", value: "ptitbac"},
]

function GamesSelect({games, setGames} : {games: Game[], setGames: Dispatch<SetStateAction<Game[]>>}) {
    return (
        <Popover>
            <PopoverTrigger asChild>
                <Button
                    variant="outline"
                    role="combobox"
                    className={cn(
                        "w-[200px] justify-between",
                        "text-muted-foreground"
                    )}
                >
                    Selection des jeux ({games.length}/{allGames.length})
                    <ChevronsUpDown className="opacity-50"/>
                </Button>
            </PopoverTrigger>
            <PopoverContent className="w-[200px] p-0">
                <Command>
                    <CommandInput
                        placeholder="Rechercher un jeu..."
                        className="h-9"
                    />
                    <CommandList>
                        <CommandEmpty>Aucun résultat.</CommandEmpty>
                        <CommandGroup>
                            {allGames.map((game) => (
                                <CommandItem
                                    value={game.label}
                                    key={game.value}
                                    onSelect={() => {
                                        // Add or remove the game from the list
                                        setGames((prev) => {
                                            // Vérification si le jeu est déjà dans la liste en comparant `value` des objets `Game`
                                            if (prev.some((g) => g.value === game.value)) {
                                                // Si le jeu est déjà présent, on le retire
                                                return prev.filter((g) => g.value !== game.value);
                                            } else {
                                                // Si le jeu n'est pas dans la liste, on l'ajoute
                                                return [...prev, game];
                                            }
                                        });
                                    }}
                                >
                                    {game.label}
                                    <Check
                                        className={cn(
                                            "ml-auto transition-all duration-300",
                                            games.some(value => value === game)
                                                ? "scale-100"
                                                : "scale-0"
                                        )}
                                    />
                                </CommandItem>
                            ))}
                        </CommandGroup>
                    </CommandList>
                </Command>
            </PopoverContent>
        </Popover>
    );
}

export default function Lobby({code, owner, players}: LobbyProps) {
    const [copied, setCopied] = useState(false);
    const [games, setGames] = useState<Game[]>(allGames);

    const copyToClipboard = () => {
        navigator.clipboard.writeText(code);
        setCopied(true);
        setTimeout(() => setCopied(false), 2000);
    };

    return (
        <div className="flex flex-col items-center space-y-4 p-4">
            <Image src="/logo.png" alt="Logo" width={200} height={200}/>
            {/*<div className="text-center text-gray-500">Connecté en tant que {username}.</div>*/}

            <div className="flex w-full max-w-5xl border rounded-lg shadow-md p-4">
                <div className="flex flex-col items-center flex-1 space-y-4">

                    <div className="flex items-center">
                        <label className="mr-2">Code: </label>
                        <InputOTP maxLength={6} value={code}>
                            <InputOTPGroup>
                                <InputOTPSlot index={0}/>
                                <InputOTPSlot index={1}/>
                                <InputOTPSlot index={2}/>
                            </InputOTPGroup>
                            <InputOTPSeparator/>
                            <InputOTPGroup>
                                <InputOTPSlot index={3}/>
                                <InputOTPSlot index={4}/>
                                <InputOTPSlot index={5}/>
                            </InputOTPGroup>
                        </InputOTP>

                        <Button
                            variant="default"
                            size="icon"
                            className="relative ml-2 rounded-md cursor-pointer"
                            onClick={copyToClipboard}
                            aria-label={copied ? "Copied" : "Copy to clipboard"}
                        >
                            <span className="sr-only">{copied ? "Copied" : "Copy"}</span>
                            <Copy
                                className={`h-4 w-4 transition-all duration-300 ${
                                    copied ? "scale-0" : "scale-100"
                                }`}
                            />
                            <Check
                                className={`absolute inset-0 m-auto h-4 w-4 transition-all duration-300 ${
                                    copied ? "scale-100" : "scale-0"
                                }`}
                            />
                        </Button>
                    </div>

                    {/* Texte : Configuration */}
                    <div className="text-lg">Configuration</div>
                    <GamesSelect games={games} setGames={setGames} />


                    <Button variant={"success"} className={"cursor-pointer"}>Lancer la partie</Button>
                </div>

                <div className="w-px bg-gray-300 mx-4"/>

                <div className="flex-1 space-y-4">
                    <div className="text-center text-lg">Liste des joueurs</div>
                    <PlayersList players={players} owner={owner}/>
                </div>
            </div>
        </div>
    );
}


export function PlayersList({players, owner}: { players: string[], owner: string }) {
    return (
        <div className="rounded-md border">
            <ScrollArea className={"w-72 max-h-72 overflow-y-auto"}>
                <Table>
                    <TableHeader>
                        <TableRow>
                            <TableHead>Rôle</TableHead>
                            <TableHead>Joueurs</TableHead>
                        </TableRow>
                    </TableHeader>
                    <TableBody>
                        {players.map((player, index) => (
                            <TableRow key={index}>
                                <TableCell>{
                                    player === owner ? <Crown color={"#FFD700"}/> : <User size={24}/>
                                }</TableCell>
                                <TableCell>{player}</TableCell>
                            </TableRow>
                        ))}
                    </TableBody>
                </Table>
            </ScrollArea>
        </div>
    );
}